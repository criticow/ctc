#pragma once

#include <ecs/components/components.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Engine;

class CameraSystem
{
  public:
  Projection *projection = nullptr;
  Transform *transform = nullptr;

  CameraSystem(){};
  glm::mat4 viewMatrix = glm::mat4(1.0f);
  glm::mat4 projectionMatrix = glm::mat4(1.0f);
  glm::vec3 target = glm::vec3(0.0f);

  void render();
  void update();
};