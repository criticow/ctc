#include "logger.hpp"

std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec2)
{
  os << "(" << vec2.x << ", " << vec2.y << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec3)
{
  os << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec4)
{
  os << "(" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::mat4 &mat4)
{
  for(int i = 0; i < 4; i++)
  {
    os << "[ ";
    for(int j = 0; j < 4; j++)
    {
      os << mat4[i][j] << (j < 3 ? ",\t" : "");
    }
    os << " ]";
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const glm::quat &quat)
{
  os << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const btVector3 &vec3)
{
  os << "(" << vec3.x() << ", " << vec3.y() << ", " << vec3.z() << ")";
  return os;
}
