#pragma once

#include <ecs/components/components.hpp>
#include <ecs/entities/entity.hpp>
#include <resources/shapes.hpp>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

class CubeEntity : public Entity
{
  public:
  Transform* transform = nullptr;
  Mesh* mesh = nullptr;
  Material* material = nullptr;
  Collider* collider = nullptr;
  GhostTrigger* trigger = nullptr;

  CubeEntity();
  void createCollider(float mass = 0.0f, glm::vec3 inertia = glm::vec3(0.0f));
  void createGhostTrigger(glm::vec3 size);
  void updateMesh(const Mesh& newMesh);
  void updateMaterial(const Material& newMaterial);
};