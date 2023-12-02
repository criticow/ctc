#include "window.hpp"
#include <core/engine.hpp>

Window::Window(WindowSpecification windowSpec)
{
  LOGGER_DEBUG("Creating Window");
  ASSERT(!glfwInit(), "Could not init glfw");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowSpec.glVersionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowSpec.glVersionMinor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, windowSpec.glProfile);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  #ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  #endif

  this->width = windowSpec.width;
  this->height = windowSpec.height;
  this->handle = glfwCreateWindow(windowSpec.width, windowSpec.height, windowSpec.title, nullptr, nullptr);
  ASSERT(!this->handle, "Could not create GLFW window");
  glfwMakeContextCurrent(this->handle);
  ASSERT(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Could not load OpenGL");

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  this->setCallbacks(this->handle);
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose(handle);
}

void Window::close()
{
  glfwSetWindowShouldClose(this->handle, GLFW_TRUE);
}

void Window::cleanup()
{
  LOGGER_DEBUG("Destroying window");
  glfwTerminate();
}

void Window::handleEvents()
{
  glfwPollEvents();
}

void Window::swapBuffers()
{
  glfwSwapBuffers(this->handle);
}

void Window::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setBackground(glm::vec4 color)
{
  glClearColor(color.x, color.y, color.z, color.w);
}

void Window::setWindowUserPointer(Engine *engine)
{
  LOGGER_DEBUG("Setting window user pointer");
  glfwSetWindowUserPointer(this->handle, engine);
}

void Window::setVsync(bool active)
{
  glfwSwapInterval(active);
}

void Window::setCallbacks(GLFWwindow *window)
{
  LOGGER_DEBUG("Setting window callbacks");

  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if(flags & GL_CONTEXT_FLAG_DEBUG_BIT)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(this->glDebugOutput, nullptr);
    LOGGER_DEBUG("Setting DebugMessageCallback");
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
  }

  LOGGER_DEBUG("Setting FramebufferSizeCallback");
  glfwSetFramebufferSizeCallback(this->handle, framebufferSizeCallback);
  glfwSetCursorPosCallback(this->handle, mouseCallback);
}

void Window::glDebugOutput(
  GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const char *message,
  const void *userParam
)
{
  // ignore non-significant error/warning codes
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::ostringstream sstream;

  sstream << "\nDebug message (" << id << "): " <<  message << "\n";

  switch (source)
  {
    case GL_DEBUG_SOURCE_API:             sstream << "Source: API\n"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sstream << "Source: Window System\n"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sstream << "Source: Shader Compiler\n"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     sstream << "Source: Third Party\n"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     sstream << "Source: Application\n"; break;
    case GL_DEBUG_SOURCE_OTHER:           sstream << "Source: Other\n"; break;
  }

  switch (type)
  {
    case GL_DEBUG_TYPE_ERROR:               sstream << "Type: Error\n"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: sstream << "Type: Deprecated Behaviour\n"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  sstream << "Type: Undefined Behaviour\n"; break; 
    case GL_DEBUG_TYPE_PORTABILITY:         sstream << "Type: Portability\n"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         sstream << "Type: Performance\n"; break;
    case GL_DEBUG_TYPE_MARKER:              sstream << "Type: Marker\n"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          sstream << "Type: Push Group\n"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           sstream << "Type: Pop Group\n"; break;
    case GL_DEBUG_TYPE_OTHER:               sstream << "Type: Other\n"; break;
  }
  
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:         sstream << "Severity: high\n"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       sstream << "Severity: medium\n"; break;
    case GL_DEBUG_SEVERITY_LOW:          sstream << "Severity: low\n"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: sstream << "Severity: notification\n"; break;
  }

  LOGGER_ERROR(sstream.str());
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  if(width == 0 || height == 0)
    return;

  glViewport(0, 0, width, height);

  Engine *engine = reinterpret_cast<Engine *>(glfwGetWindowUserPointer(window));
  ASSERT(!engine, "Engine instance is not set on the window user pointer");

  engine->window.width = width;
  engine->window.height = height;
  engine->render();
}

void Window::mouseCallback(GLFWwindow * window, double xPos, double yPos)
{
  Engine *engine = reinterpret_cast<Engine *>(glfwGetWindowUserPointer(window));
  ASSERT(!engine, "Engine instance is not set on the window user pointer");

  engine->window.mouse = glm::vec2(xPos, yPos);
}
