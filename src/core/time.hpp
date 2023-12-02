#pragma once

#include <format>

#include <core/window.hpp>
#include <core/logger.hpp>

#include <glm/glm.hpp>
#include <sstream>

class Time
{
  public:
  Time(){};
  Time(Window window);

  void update();
  float deltaTime;
  float lastTime;
  float msAverage;
  float fpsAverage;

  private:
  float deltaTimeSum;
  float updateTime;
  int sumCount;
  Window window;
};