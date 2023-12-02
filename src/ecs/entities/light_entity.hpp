#pragma once

#include <ecs/components/components.hpp>
#include <ecs/entities/entity.hpp>

class LightEntity : public Entity
{
  public:
  Transform* transform = nullptr;
  Light* light = nullptr;

  LightEntity(LightType type);
};