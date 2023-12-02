#include "engine.hpp"

// Static members
Window Engine::window;
Time Engine::time;
Input Engine::input;
ResourceManager Engine::resourceManager;
CameraSystem Engine::cameraSystem;
Physics Engine::physics;
entt::registry Engine::registry;

Engine::Engine(int width, int height, const char* title)
{
  WindowSpecification windowSpec;
  windowSpec.height = height;
  windowSpec.width = width;
  windowSpec.title = title;

  this->window = Window(windowSpec);
  this->time = Time(this->window);

  this->window.setWindowUserPointer(this);
}

Engine::~Engine()
{
  LOGGER_DEBUG("Destroying engine");
  this->window.cleanup();
  this->resourceManager.cleanup();
}

void Engine::baseSetup()
{
  this->window.setBackground(this->backgroundColor);
  this->window.setVsync(true);
  this->resourceManager.setShader("default", shaders::defaultShader());
  this->resourceManager.setShader("line", shaders::lineShader());
}

void Engine::baseUpdate()
{
  this->time.update();
  this->input.update(this->window);
  this->physics.stepSimulation(this->time.deltaTime);

  this->cameraSystem.update();

  auto collisionView = this->registry.view<Collider, Transform>();
  for(auto [entity, collision, transform] : collisionView.each())
  {
    btTransform trans;
    collision.motionState->getWorldTransform(trans);

    btVector3 position = trans.getOrigin();
    btQuaternion rotation = trans.getRotation();

    transform.position = glm::vec3(position.getX(), position.getY(), position.getZ());
    transform.rotation = glm::degrees(glm::eulerAngles(glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ())));
  }
}

void Engine::render()
{
  this->window.clear();

  // Systems
  if(this->renderMode < 2)
  {
    this->cameraSystem.render();
    LightSystem::render();
    MeshSystem::render();
  }

  if(this->renderMode > 0)
  {
    this->physics.debugDraw();
  }

  this->window.swapBuffers();
}

void Engine::toggleRenderMode()
{
  this->renderMode = this->renderMode == 2 ? 0 : this->renderMode + 1;
}

void Engine::run()
{
  Engine::baseSetup();
  this->setup();

  while(this->window.isOpen())
  {
    this->window.handleEvents();

    this->baseUpdate();
    this->update();

    this->render();
  }
}