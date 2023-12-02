#include "capsule_entity.hpp"

CapsuleEntity::CapsuleEntity()
{
  this->transform = addComponent<Transform>(Transform{});
  this->mesh = addComponent<Mesh>(shapes::capsule());
  this->material = addComponent<Material>(Material{});
}

void CapsuleEntity::createCollider(float mass, glm::vec3 inertia)
{
  this->collider = addComponent<Collider>(Collider::CAPSULE, *this->transform, mass, inertia);
  Engine::physics.addRigidBody(this->handle, this->collider->rigidBody);
}
