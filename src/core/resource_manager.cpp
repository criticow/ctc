#include "resource_manager.hpp"

Shader &ResourceManager::getShader(const std::string &name)
{
  ASSERT(this->shaders.find(name) == this->shaders.end(), "Shader not found {}", name);
  return this->shaders[name];
}

Shader &ResourceManager::setShader(const std::string &name, const char *vShaderPath, const char *fShaderPath)
{
  std::string vShaderCode = this->readFile(vShaderPath);
  std::string fShaderCode = this->readFile(fShaderPath);

  LOGGER_DEBUG("Creating Shader: {}", name);
  this->shaders[name] = Shader(vShaderCode.c_str(), fShaderCode.c_str());
  return this->shaders[name];
}

Shader &ResourceManager::setShader(const std::string& name, Shader shader)
{
  LOGGER_DEBUG("Creating Shader: {}", name);
  this->shaders[name] = shader;
  return this->shaders[name];
}

Texture2D &ResourceManager::getTexture(const std::string &name)
{
  ASSERT(this->textures.find(name) == this->textures.end(), "Texture not found {}", name);
  return this->textures[name];
}

Texture2D &ResourceManager::setTexture(const std::string &name, const char *path)
{
  LOGGER_DEBUG("Creating Texture: {}", name);
  this->textures[name] = Texture2D(path);
  return this->textures[name];
}

Texture2D &ResourceManager::setTexture(const std::string& name, Texture2D texture)
{
  LOGGER_DEBUG("Creating Texture: {}", name);
  this->textures[name] = texture;
  return this->textures[name];
}

Model &ResourceManager::getModel(const std::string &name)
{
  ASSERT(this->models.find(name) == this->models.end(), "Model not found {}", name);
  return this->models[name];
}

Model &ResourceManager::setModel(const std::string &name, const char *path)
{
  LOGGER_DEBUG("Creating Model: {}", name);
  this->models[name] = Model(path);
  return this->models[name];
}

Model &ResourceManager::setModel(const std::string& name, Model model)
{
  LOGGER_DEBUG("Creating Model: {}", name);
  this->models[name] = model;
  return this->models[name];
}

RenderObject &ResourceManager::getRenderObject(const std::string &name)
{
  ASSERT(this->renderObjects.find(name) == this->renderObjects.end(), "RenderObject not found {}", name);
  return this->renderObjects[name];
}

RenderObject &ResourceManager::setRenderObject(const std::string &name, std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
  LOGGER_DEBUG("Creating RenderObject: {}", name);
  this->renderObjects[name] = RenderObject(vertices, indices);
  return this->renderObjects[name];
}

RenderObject &ResourceManager::setRenderObject(const std::string &name, RenderObject renderObject)
{
  LOGGER_DEBUG("Creating RenderObject: {}", name);
  this->renderObjects[name] = renderObject;
  return this->renderObjects[name];
}

void ResourceManager::cleanup()
{
  LOGGER_DEBUG("Destroying {} Shaders", this->shaders.size());
  for(auto& [name, shader] : this->shaders)
  {
    shader.destroy();
  }

  LOGGER_DEBUG("Destroying {} Textures", this->textures.size());
  for(auto& [name, texture] : this->textures)
  {
    texture.destroy();
  }

  LOGGER_DEBUG("Destroying {} Models", this->models.size());
  for(auto& [name, model] : this->models)
  {
    // Nothing to destroy here really
  }

  LOGGER_DEBUG("Destroying {} RenderObjects", this->renderObjects.size());
  for(auto& [name, renderObject] : this->renderObjects)
  {
    renderObject.destroy();
  }
}

std::string ResourceManager::readFile(const char *path)
{
  std::ifstream file(path);
  ASSERT(!file.is_open(), "Could not open file {}", path);

  std::ostringstream sstream;
  sstream << file.rdbuf();

  return sstream.str();
}
