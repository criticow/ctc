set(SOURCE_FILES
  # CORE
  core/logger.cpp
  core/window.cpp
  core/engine.cpp
  core/time.cpp
  core/input.cpp
  core/resource_manager.cpp
  core/physics.cpp
  core/debug_drawer.cpp
  core/line_renderer.cpp
  # RESOURCES
  resources/shader.cpp
  resources/texture.cpp
  resources/model.cpp
  resources/render_object.cpp
  resources/shapes.cpp
  resources/default_shaders.cpp
  # ECS/COMPONENTS
  ecs/components/components.cpp
  # ECS/SYSTEMS
  ecs/systems/camera_system.cpp
  ecs/systems/light_system.cpp
  ecs/systems/mesh_system.cpp
  # ECS/ENTITIES
  ecs/entities/light_entity.cpp
  ecs/entities/camera_entity.cpp
  ecs/entities/cube_entity.cpp
  ecs/entities/sphere_entity.cpp
  ecs/entities/capsule_entity.cpp
)

set(HEADER_FILES
  # CORE
  core/core.hpp
  core/logger.hpp
  core/window.hpp
  core/engine.hpp
  core/time.hpp
  core/input.hpp
  core/resource_manager.hpp
  core/physics.hpp
  core/debug_drawer.hpp
  core/line_renderer.hpp
  # RESOURCES
  resources/shader.hpp
  resources/texture.hpp
  resources/model.hpp
  resources/render_object.hpp
  resources/shapes.hpp
  resources/default_shaders.hpp
  # ECS/COMPONENTS
  ecs/components/components.hpp
  # ECS/SYSTEMS
  ecs/systems/systems.hpp
  ecs/systems/camera_system.hpp
  ecs/systems/light_system.hpp
  ecs/systems/mesh_system.hpp
  # ECS/ENTITIES
  ecs/entities/entities.hpp
  ecs/entities/light_entity.hpp
  ecs/entities/entity.hpp
  ecs/entities/camera_entity.hpp
  ecs/entities/cube_entity.hpp
  ecs/entities/sphere_entity.hpp
  ecs/entities/capsule_entity.hpp
)

add_library(ctc ${SOURCE_FILES} ${HEADER_FILES})

# Locating packages installed globally via vcpkg
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

# Linking vcpkg installed packages
target_link_libraries(ctc PUBLIC
  glfw
  EnTT::EnTT
  glm::glm
  glad::glad
  assimp::assimp
  ${BULLET_LIBRARIES}
)

target_include_directories(ctc PUBLIC
  $<BUILD_INTERFACE:${ROOT_DIR}/src>
)