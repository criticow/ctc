#include "enemy.hpp"

Enemy::Enemy(
  const glm::vec3 &position,
  const glm::vec3& color,
  const glm::vec3& constraintStart,
  const glm::vec3& constraintEnd,
  const glm::vec3& direction
)
{
  transform->position = position;
  material->diffuseColor = color;
  createCollider(0.0f);
  collider->rigidBody->setCollisionFlags(
    collider->rigidBody->getCollisionFlags() |
    btCollisionObject::CF_KINEMATIC_OBJECT
  );
  collider->rigidBody->setActivationState(DISABLE_DEACTIVATION);
  this->constraintStart = constraintStart;
  this->constraintEnd = constraintEnd;
  this->direction = direction;
  this->velocity = direction * speed;
}

void Enemy::update()
{
  btVector3 enemyPosition = collider->rigidBody->getWorldTransform().getOrigin();
  enemyPosition += btVector3(velocity.x, velocity.y, velocity.z);

  if(
    this->direction.x > 0 &&
    (enemyPosition.x() > this->constraintEnd.x - 0.1f || enemyPosition.x() < this->constraintStart.x - 0.1f)
  )
  {
    this->velocity = -this->velocity;
  }

  if(
    this->direction.z > 0 &&
    (enemyPosition.z() > this->constraintStart.z - 0.1f || enemyPosition.z() < this->constraintEnd.z - 0.1f)
  )
  {
    this->velocity = -this->velocity;
  }

  btTransform newTransform;
  newTransform.setIdentity();
  newTransform.setOrigin(enemyPosition);

  collider->rigidBody->getMotionState()->setWorldTransform(newTransform);
}
