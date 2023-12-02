#include "components.hpp"

Collider::Collider(Type type, const Transform &transform, float mass, glm::vec3 inertia)
{
  switch(type)
  {
    case BOX:
      shape = new btBoxShape(btVector3(transform.scale.x, transform.scale.y, transform.scale.z));
      break;
    case SPHERE:
      shape = new btSphereShape(transform.scale.x);
      break;
    case CAPSULE:
      shape = new btCapsuleShape(transform.scale.x, transform.scale.y * 2.0f);
      break;
  }

  motionState = new btDefaultMotionState(
    btTransform(
      btQuaternion(transform.rotation.x, transform.rotation.y, transform.rotation.z, 1),
      btVector3(transform.position.x, transform.position.y, transform.position.z)
    )
  );

  btVector3 localInertia = btVector3(inertia.x, inertia.y, inertia.z);
  if(mass > 0)
  {
    shape->calculateLocalInertia(mass, localInertia);
  }

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, shape, localInertia);
  rigidBody = new btRigidBody(rigidBodyCI);
}

GhostTrigger::GhostTrigger(const Transform& transform, glm::vec3 size)
{
  btCollisionShape* triggerShape = new btBoxShape(btVector3(size.x, size.y, size.z));

  // Create a ghost object and associate the collision shape with it
  ghostObject = new btGhostObject();
  ghostObject->setCollisionShape(triggerShape);

  // Set the collision flags to indicate that it is a trigger
  ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

  ghostObject->setWorldTransform(
    btTransform(
      btQuaternion(transform.rotation.x, transform.rotation.y, transform.rotation.z, 1),
      btVector3(transform.position.x, transform.position.y, transform.position.z)
    )
  );
}
