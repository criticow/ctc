#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <core/logger.hpp>

class Texture2D
{
  public:
  GLuint handle = 0;
  Texture2D(void) = default;
  Texture2D(const char *path);
  void bind();
  void destroy();

  operator bool() const
  {
    return handle != 0;
  }
};