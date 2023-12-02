#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

#include <core/logger.hpp>

class Shader
{
  public:
  Shader(){};
  Shader(const char* vShaderData, const char* fShaderData);
  void init(const char *vShaderData, const char *fShaderData);
  void use();
  void destroy();
  void setInt(const std::string &name, GLint value);
  void setFloat(const std::string &name, glm::vec2 value);
  void setFloat(const std::string &name, glm::vec3 value);
  void setFloat(const std::string &name, glm::vec4 value);
  void setMatrix(const std::string &name, glm::mat4 value);

  private:
  // Variables
  GLuint handle;
  std::unordered_map<std::string, GLint> locations;
  // Methods
  GLint getLocation(const std::string &name);
  void validate(GLuint handle, const std::string &type);
};