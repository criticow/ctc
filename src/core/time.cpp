#include "time.hpp"

Time::Time(Window window)
{
  LOGGER_DEBUG("Creating Time");
  this->deltaTime     = 0.0f;
  this->lastTime      = 0.0f;
  this->deltaTimeSum  = 0.0f;
  this->sumCount      = 0.0f;
  this->msAverage     = 0.0f;
  this->fpsAverage    = 0.0f;
  
  this->window = window;
}

void Time::update()
{
  float currentTime = (float)glfwGetTime();
  this->deltaTime = currentTime - lastTime;
  this->lastTime = currentTime;
  this->deltaTimeSum += this->deltaTime;
  this->sumCount++;

  // Update each second
  if(currentTime - this->updateTime >= 1.0f)
  {
    this->msAverage = this->deltaTimeSum * 1000.0f / this->sumCount;
    this->fpsAverage = 1.0f / (this->deltaTimeSum / this->sumCount);
    glfwSetWindowTitle(this->window.handle, std::format("{:.2f} ms {:.2f} fps", this->msAverage, this->fpsAverage).c_str());
    this->deltaTimeSum = 0.0f;
    this->sumCount = 0.0f;
    this->updateTime = currentTime;
  }
}