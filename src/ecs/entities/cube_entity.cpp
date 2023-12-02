#include "cube_entity.hpp"

CubeEntity::CubeEntity()
{
  this->transform = addComponent<Transform>(Transform{});
  this->mesh = addComponent<Mesh>(shapes::cube());
  this->material = addComponent<Material>(Material{});
}

void CubeEntity::createCollider(float mass, glm::vec3 inertia)
{
  this->collider = addComponent<Collider>(Collider::BOX, *this->transform, mass, inertia);
  Engine::physics.addRigidBody(this->handle, this->collider->rigidBody);
}

void CubeEntity::createGhostTrigger(glm::vec3 size)
{
  this->trigger = addComponent<GhostTrigger>(*this->transform, size);
  Engine::physics.addGhostTrigger(this->handle, this->trigger->ghostObject);
}

void CubeEntity::updateMesh(const Mesh &newMesh)
{
  this->mesh = addComponent<Mesh>(newMesh);
}

void CubeEntity::updateMaterial(const Material &newMaterial)
{
  this->material = addComponent<Material>(newMaterial);
}
