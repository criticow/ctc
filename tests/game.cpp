#include "game.hpp"

void Game::setup()
{
  Model ball("data/models/playerball.gltf");
  Model coin("data/models/coin.gltf");

  CameraEntity mainCamera;
  mainCamera.projection->active = true;
  mainCamera.transform->position = glm::vec3(0.0f, 15.0f, 10.0f);
  mainCamera.transform->rotation.x = -45.0f;

  LightEntity directionalLight(DIRECTIONAL);
  directionalLight.transform->rotation = glm::vec3(-40.0f, 60.0f, 0.0f);

  CubeEntity coinEntity;
  coinEntity.transform->position = glm::vec3(5.0f, 2.0f, 0.0f);
  coinEntity.material->diffuseColor = glm::vec3(0.97f, 0.73f, 0.0f);
  coinEntity.updateMesh(coin.mesh);
  coinEntity.createGhostTrigger(glm::vec3(1.0f));

  // enemies.push_back(Enemy(
  //   glm::vec3(-15.0f, 2.0f, 0.0f), // Position
  //   glm::vec3(1.0f, 0.5f, 0.31f),  // Color
  //   glm::vec3(0.0f, 0.0f, 8.0f),   // Constraint start
  //   glm::vec3(0.0f, 0.0f, -8.0f),  // Constraint end
  //   glm::vec3(0.0f, 0.0f, 0.3f)    // Direction
  // ));

  // enemies.push_back(Enemy(
  //   glm::vec3(-15.0f, 2.0f, 12.0f),
  //   glm::vec3(1.0f, 0.5f, 0.31f),
  //   glm::vec3(-15.0f, 0.0f, 0.0f),
  //   glm::vec3(-2.0f, 0.0f, 0.0f),
  //   glm::vec3(0.1f, 0.0f, 0.0f)
  // ));

  // enemies.push_back(Enemy(
  //   glm::vec3(-15.0f, 2.0f, -12.0f),
  //   glm::vec3(1.0f, 0.5f, 0.31f),
  //   glm::vec3(-15.0f, 0.0f, 0.0f),
  //   glm::vec3(-2.0f, 0.0f, 0.0f),
  //   glm::vec3(0.1f, 0.0f, 0.0f)
  // ));

  CubeEntity floor;
  floor.transform->scale = glm::vec3(20.0f, 1.0f, 20.0f);
  floor.createCollider();

  player = Player(this->input, ball, glm::vec3(0.0f, 2.0f, 0.0f));
  player.setConstraint(
    glm::vec3(-floor.transform->scale.x, player.transform->position.y * 0.5, -floor.transform->scale.z),
    glm::vec3(floor.transform->scale.x, player.transform->position.y * 0.5, floor.transform->scale.z)
  );

  CubeEntity rightWall;
  rightWall.transform->position = glm::vec3(floor.transform->scale.x + 1.0f, 2.0f, 0.0f);
  rightWall.transform->scale.z = floor.transform->scale.z;
  rightWall.createCollider(0.0f);

  CubeEntity leftWall;
  leftWall.transform->position = glm::vec3(-floor.transform->scale.x - 1.0f, 2.0f, 0.0f);
  leftWall.transform->scale.z = floor.transform->scale.z;
  leftWall.createCollider(0.0f);

  CubeEntity topWall;
  topWall.transform->position = glm::vec3(0.0f, 2.0f, -floor.transform->scale.z - 1.0f);
  topWall.transform->scale.x = floor.transform->scale.x + 2.0f;
  topWall.createCollider(0.0f);

  CubeEntity bottomWall;
  bottomWall.transform->position = glm::vec3(0.0f, 2.0f, floor.transform->scale.z + 1.0f);
  bottomWall.transform->scale.x = floor.transform->scale.x + 2.0f;
  bottomWall.createCollider(0.0f);
}

void Game::update()
{
  cameraSystem.target = this->player.transform->position;

  if(this->input.actionPressed("cancel"))
  {
    this->window.close();
  }

  static bool vSyncState = true;
  if(this->input.actionPressed("f8"))
  {
    vSyncState = !vSyncState;
    this->window.setVsync(vSyncState);
  }

  if(this->input.actionPressed("f7"))
  {
    this->toggleRenderMode();
  }

  if(isGameOver)
  {
    return;
  }

  player.update();

  for(auto& enemy : enemies)
  {
    enemy.update();
    if(physics.isColliding(this->player.collider->rigidBody, enemy.collider->rigidBody))
    {
      player.speed = 0;
      player.update();
      isGameOver = true;
    }
  }
}