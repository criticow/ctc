#include "shader.hpp"

Shader::Shader(const char *vShaderData, const char *fShaderData)
{
  this->init(vShaderData, fShaderData);
}

void Shader::init(const char *vShaderData, const char *fShaderData)
{
  // Vertex Shader
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShader, 1, &vShaderData, nullptr);
  glCompileShader(vShader);
  this->validate(vShader, "VERTEX");
  // Fragment Shader
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShader, 1, &fShaderData, nullptr);
  glCompileShader(fShader);
  this->validate(fShader, "FRAGMENT");
  // Shader Program
  this->handle = glCreateProgram();
  glAttachShader(this->handle, vShader);
  glAttachShader(this->handle, fShader);
  glLinkProgram(this->handle);
  this->validate(this->handle, "PROGRAM");
  // Cleanup
  glDeleteShader(vShader);
  glDeleteShader(fShader);
}

void Shader::use()
{
  glUseProgram(this->handle);
}

void Shader::destroy()
{
  glDeleteProgram(this->handle);
}

void Shader::setInt(const std::string &name, GLint value)
{
  glUniform1i(this->getLocation(name), value);
}

void Shader::setFloat(const std::string &name, glm::vec2 value)
{
  glUniform2fv(this->getLocation(name), 1, &value[0]);
}

void Shader::setFloat(const std::string &name, glm::vec3 value)
{
  glUniform3fv(this->getLocation(name), 1, &value[0]);
}

void Shader::setFloat(const std::string &name, glm::vec4 value)
{
  glUniform4fv(this->getLocation(name), 1, &value[0]);
}

void Shader::setMatrix(const std::string &name, glm::mat4 value)
{
  glUniformMatrix4fv(this->getLocation(name), 1, GL_FALSE, &value[0][0]);
}

GLint Shader::getLocation(const std::string &name)
{
  if(this->locations.find(name) != this->locations.end())
  {
    return this->locations[name];
  }

  this->locations[name] = glGetUniformLocation(this->handle, name.c_str());
  return this->locations[name];
}
void Shader::validate(GLuint handle, const std::string &type)
{
  GLint success;
  GLchar infoLog[1024];

  if(type == "PROGRAM")
  {
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if(!success)
    {
      glGetProgramInfoLog(handle, sizeof(infoLog), nullptr, infoLog);
      LOGGER_ERROR("Failed to link shader program:\n{}", infoLog);
    }
    return;
  }

  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(handle, sizeof(infoLog), nullptr, infoLog);
    LOGGER_ERROR("Failed to compile {} shader:\n{}", type, infoLog);
  }
}
