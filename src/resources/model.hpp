#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// #include <entt/entity/registry.hpp>
// #include <entt/entity/entity.hpp>

#include <core/logger.hpp>
#include <resources/texture.hpp>
#include <ecs/components/components.hpp>

#include <filesystem>

#include <iostream>
#include <sstream>

class Model
{
  public:
  Model(){};
  Model(const char* path);
  void loadModel(const char* path);
  // Variables
  Mesh mesh;
  Material material;
};