#pragma once

#include <ecs/components/components.hpp>

class RenderObject
{
  public:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  GLuint instanceVBO;

  RenderObject(){};
  RenderObject(const std::vector<Vertex> &vertices, const std::vector<GLuint> indices);
  void bind();
  void render(GLuint count);
  void destroy();
};