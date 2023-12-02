#pragma once

#include <glm/glm.hpp>
#include <core/input.hpp>
#include <ecs/entities/sphere_entity.hpp>
#include <resources/model.hpp>
#include <core/logger.hpp>

class Player : public SphereEntity
{
  public:
  Player(){};
  Player(Input& input, const Model& model, const glm::vec3& position);
  ~Player();

  float speed = 10.0f;
  glm::vec3 linearVelocity = glm::vec3(0.0f, -5.0f, 0.0f);
  glm::vec3 angularVelocity = glm::vec3(0.0f);
  Input* input;

  void update();
  void setConstraint(glm::vec3 start, glm::vec3 end);
};