#pragma once

#include <entt/entt.hpp>
#include <ecs/components/components.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <resources/shader.hpp>


class Engine;
class LightSystem
{
  public:
  LightSystem(){};
  static void render();
};