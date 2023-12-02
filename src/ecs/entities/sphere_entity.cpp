#include "sphere_entity.hpp"

SphereEntity::SphereEntity()
{
  this->transform = addComponent<Transform>(Transform{});
  this->mesh = addComponent<Mesh>(shapes::sphere());
  this->material = addComponent<Material>(Material{});
}

void SphereEntity::createCollider(float mass, glm::vec3 inertia)
{
  this->collider = addComponent<Collider>(Collider::SPHERE, *this->transform, mass, inertia);
  Engine::physics.addRigidBody(this->handle, this->collider->rigidBody);
  this->collider->rigidBody->setUserPointer((void*)this->handle);
}

void SphereEntity::updateMesh(const Mesh &mesh)
{
  this->mesh = addComponent<Mesh>(mesh);
}

void SphereEntity::updateMaterial(const Material &material)
{
  this->material = addComponent<Material>(material);
}
