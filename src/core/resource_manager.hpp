#pragma once

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

#include <core/logger.hpp>
#include <resources/shader.hpp>
#include <resources/texture.hpp>
#include <resources/model.hpp>
#include <resources/render_object.hpp>

class ResourceManager
{
  public:
  ResourceManager(){};

  Shader& getShader(const std::string& name);
  Shader& setShader(const std::string& name, const char* vShaderPath, const char* fShaderPath);
  Shader& setShader(const std::string& name, Shader shader);

  Texture2D& getTexture(const std::string& name);
  Texture2D& setTexture(const std::string& name, const char* path);
  Texture2D& setTexture(const std::string& name, Texture2D texture);

  Model& getModel(const std::string& name);
  Model& setModel(const std::string& name, const char* path);
  Model& setModel(const std::string& name, Model model);

  RenderObject& getRenderObject(const std::string& name);
  RenderObject& setRenderObject(const std::string& name, std::vector<Vertex> vertices, std::vector<GLuint> indices);
  RenderObject& setRenderObject(const std::string& name, RenderObject renderObject);

  template<typename T>
  bool hasResource(const std::string& name)
  {
    if(std::is_same<T, Shader>::value)
    {
      return this->shaders.find(name) != this->shaders.end();
    }

    if(std::is_same<T, Texture2D>::value)
    {
      return this->textures.find(name) != this->textures.end();
    }

    if(std::is_same<T, Model>::value)
    {
      return this->models.find(name) != this->models.end();
    }

    if(std::is_same<T, RenderObject>::value)
    {
      return this->renderObjects.find(name) != this->renderObjects.end();
    }
  }

  void cleanup();

  private:
  std::unordered_map<std::string, Shader> shaders;
  std::unordered_map<std::string, Texture2D> textures;
  std::unordered_map<std::string, Model> models;
  std::unordered_map<std::string, RenderObject> renderObjects;

  std::string readFile(const char* path);
};