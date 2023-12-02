#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <core/logger.hpp>
#include <glm/glm.hpp>

struct WindowSpecification
{
  int glVersionMajor = 4;
  int glVersionMinor = 6;
  int glProfile = GLFW_OPENGL_CORE_PROFILE;
  int width = 800;
  int height = 600;
  const char* title = "OpenGL";
};

class Engine;

class Window
{
  public:
  Window(){};
  Window(WindowSpecification windowSpec);

  GLFWwindow *handle;
  int width;
  int height;
  glm::vec2 mouse;

  bool isOpen();
  void close();
  void cleanup();
  void handleEvents();
  void swapBuffers();
  void clear();
  void setBackground(glm::vec4 color);
  void setWindowUserPointer(Engine *engine);
  void setVsync(bool active);

  private:
  void setCallbacks(GLFWwindow *window);
  static void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char *message, const void *userParam);
  static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  static void mouseCallback(GLFWwindow *window, double xPos, double yPos);
};