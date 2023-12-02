#include "camera_entity.hpp"

CameraEntity::CameraEntity()
{
  this->transform = addComponent<Transform>(Transform{});
  this->projection = addComponent<Projection>(Projection{});
}