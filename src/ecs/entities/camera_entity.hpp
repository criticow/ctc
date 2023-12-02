#pragma once

#include <ecs/components/components.hpp>
#include <ecs/entities/entity.hpp>

class CameraEntity : public Entity
{
  public:
  Transform* transform = nullptr;
  Projection* projection = nullptr;

  CameraEntity();
};