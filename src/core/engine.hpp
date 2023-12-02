#pragma once

#include <core/window.hpp>
#include <core/time.hpp>
#include <core/input.hpp>
#include <core/resource_manager.hpp>
#include <resources/default_shaders.hpp>
#include <ecs/systems/systems.hpp>
#include <ecs/components/components.hpp>
#include <core/physics.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <entt/entt.hpp>

class Engine
{
  public:
  static Window window;
  static Time time;
  static Input input;
  static ResourceManager resourceManager;
  static CameraSystem cameraSystem;
  static Physics physics;
  static entt::registry registry;

  glm::vec4 backgroundColor = glm::vec4(glm::vec3(0.298f), 1.0f);

  explicit Engine(int width, int height, const char* title);
  ~Engine();

  void run();
  virtual void setup(){};
  virtual void update(){};
  void render();
  void toggleRenderMode();

  private:
  // 0 = Normal
  // 1 = All
  // 2 = Debug
  int renderMode = 0;
  void baseSetup();
  void baseUpdate();
};