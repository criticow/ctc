#include "camera_system.hpp"
#include <core/engine.hpp>

void CameraSystem::render()
{
  Shader& shader = Engine::resourceManager.getShader("default");
  shader.use();
  
  if(transform)
  {
    shader.setFloat("viewPos", transform->position);
  }
}

void CameraSystem::update()
{
  float width = static_cast<float>(Engine::window.width);
  float height = static_cast<float>(Engine::window.height);

  auto cameraView = Engine::registry.view<Projection, Transform>();
  for(auto [entity, projection, transform] : cameraView.each())
  {
    if(projection.active)
    {
      this->projection = &projection;
      this->transform = &transform;
    }
  }

  // No active camera found
  if(!this->transform)
  {
    return;
  }

  glm::mat4 rotatedMatrix = glm::mat4(1.0f);

  glm::vec3 finalPosition = this->transform->position + this->target;

  // Apply yaw, pitch, and roll
  rotatedMatrix = glm::rotate(rotatedMatrix, -glm::radians(this->transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll
  rotatedMatrix = glm::rotate(rotatedMatrix, -glm::radians(this->transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
  rotatedMatrix = glm::rotate(rotatedMatrix, -glm::radians(this->transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw

  glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 right   = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
  glm::vec3 up      = glm::normalize(glm::cross(right, forward));

  viewMatrix = glm::lookAt(finalPosition, finalPosition + forward, up);
  viewMatrix = rotatedMatrix * viewMatrix;

  if(this->projection->type == PERSPECTIVE)
  {
    projectionMatrix = glm::perspective(
      glm::radians(this->projection->fov),
      width / height,
      this->projection->near,
      this->projection->far
    );
    return;
  }

  projectionMatrix = glm::ortho(0.0f, width, height, 0.0f, this->projection->near, this->projection->far);
}