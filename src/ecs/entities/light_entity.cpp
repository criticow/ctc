#include "light_entity.hpp"

LightEntity::LightEntity(LightType type)
{
  this->transform = addComponent<Transform>(Transform{});
  this->light = addComponent<Light>(Light{type});
}