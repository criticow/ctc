#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"

Texture2D::Texture2D(const char *path)
{
  glGenTextures(1, &this->handle);
  glBindTexture(GL_TEXTURE_2D, this->handle);

  int width, height, channels;
  unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

  ASSERT(!data, "Could not load texture {}", path);

  GLenum format;

  if(channels == 1) { format = GL_RED; }
  else if(channels == 3) { format = GL_RGB; }
  else { format = GL_RGBA; }

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(data);
}

void Texture2D::bind()
{
  glBindTexture(GL_TEXTURE_2D, this->handle);
}

void Texture2D::destroy()
{
  glDeleteTextures(1, &this->handle);
}