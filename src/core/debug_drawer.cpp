#include "debug_drawer.hpp"
#include <core/engine.hpp>

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
  this->lineRenderer.submit({
    glm::vec3(from.x(), from.y(), from.z()),
    glm::vec3(to.x(), to.y(), to.z()),
    glm::vec3(color.x(), color.y(), color.z())
  });
}

void DebugDrawer::reportErrorWarning(const char *warningString)
{
  LOGGER_WARN("Bullet3 Warning:\n{}", warningString);
}

void DebugDrawer::drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{
  (void)lifeTime;

  btVector3 to = PointOnB + normalOnB * distance;
  drawLine(PointOnB, to, color);

  const float contactPointSize = 0.05f;
  btVector3 p0 = PointOnB - normalOnB * contactPointSize;
  btVector3 p1 = PointOnB + normalOnB * contactPointSize;
  drawLine(p0, p1, color);
}
