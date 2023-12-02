#include "line_renderer.hpp"
#include <core/engine.hpp>

void LineRenderer::submit(Line line)
{
  this->lines.emplace_back(line);
}

void LineRenderer::render()
{
  Shader& lineShader = Engine::resourceManager.getShader("line");
  lineShader.use();
  lineShader.setMatrix("projectionView", Engine::cameraSystem.projectionMatrix * Engine::cameraSystem.viewMatrix);

  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->verticesVBO);
  glGenBuffers(1, &this->colorsVBO);

  glBindVertexArray(this->VAO);

  std::vector<glm::vec3> vertices;
  vertices.reserve(this->lines.size() * 2);

  std::vector<glm::vec3> colors;
  colors.reserve(this->lines.size());

  for(Line line : this->lines)
  {
    vertices.push_back(line.from);
    vertices.push_back(line.to);
    colors.push_back(line.color);
  }

  glBindBuffer(GL_ARRAY_BUFFER, this->verticesVBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);


  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, this->colorsVBO);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
  glVertexAttribDivisor(1, 1);

  glDrawArrays(GL_LINES, 0, vertices.size());
}

void LineRenderer::clear()
{
  this->lines.clear();

  glDeleteBuffers(1, &verticesVBO);
  glDeleteBuffers(1, &colorsVBO);
  glDeleteVertexArrays(1, &VAO);
}
