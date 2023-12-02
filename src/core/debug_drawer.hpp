#pragma once

#include <LinearMath/btIDebugDraw.h>
#include <glad/glad.h>
#include <core/logger.hpp>
#include <core/line_renderer.hpp>

class Engine;
class DebugDrawer : public btIDebugDraw
{
  public:
  LineRenderer lineRenderer;
  DebugDrawer(){};
  void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
  void draw3dText(const btVector3& location, const char* textString) override {};

  void setDebugMode(int debugMode) override {
    this->m_debugMode = debugMode;
  };

  int getDebugMode() const override {
    return m_debugMode;
  };

  void reportErrorWarning(const char* warningString) override;
  void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
  private:
  int m_debugMode;
};