#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <resources/render_object.hpp>
#include <glad/glad.h>

struct Line
{
  glm::vec3 from;
  glm::vec3 to;
  glm::vec3 color;
};

class Engine;

class LineRenderer
{
  public:
  LineRenderer(){};
  void submit(Line line);
  void render();
  void clear();
  private:
  std::vector<Line> lines;
  GLuint VAO;
  GLuint verticesVBO;
  GLuint colorsVBO;
};