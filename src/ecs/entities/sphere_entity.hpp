#pragma once

#include <ecs/components/components.hpp>
#include <ecs/entities/entities.hpp>
#include <resources/shapes.hpp>

class SphereEntity : public Entity
{
  public:
  Transform* transform = nullptr;
  Mesh* mesh = nullptr;
  Material* material = nullptr;
  Collider* collider = nullptr;

  SphereEntity();
  void createCollider(float mass = 0.0f, glm::vec3 inertia = glm::vec3(0.0f));
  void updateMesh(const Mesh& mesh);
  void updateMaterial(const Material& material);
};