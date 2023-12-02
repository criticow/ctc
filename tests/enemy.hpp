#pragma once

#include <ecs/entities/sphere_entity.hpp>
#include <glm/glm.hpp>
#include <core/logger.hpp>

class Enemy : public SphereEntity
{
  public:
  Enemy(){};
  Enemy(
    const glm::vec3& position,
    const glm::vec3& color,
    const glm::vec3& constraintStart,
    const glm::vec3& constraintEnd,
    const glm::vec3& direction
  );

  glm::vec3 constraintStart = glm::vec3(0.0f);
  glm::vec3 constraintEnd = glm::vec3(0.0f);
  glm::vec3 direction = glm::vec3(0.0f);
  glm::vec3 velocity = glm::vec3(0.0f);
  float speed = 1.0f;

  void update();
};