#include "player.hpp"

Player::Player(Input& input, const Model& model, const glm::vec3& position)
{
  this->input = &input;
  updateMesh(model.mesh);
  updateMaterial(model.material);
  transform->position = position;
  createCollider(1.0f);
  collider->rigidBody->setActivationState(DISABLE_DEACTIVATION); // Prevent sleep
  collider->rigidBody->setAngularFactor(btVector3(0, 0, 0));
  collider->rigidBody->setGravity(btVector3(0, 0, 0));
}

Player::~Player()
{
  // For some reason i need to cleanup the constraints here, instead on the physics class
  int numConstraints = collider->rigidBody->getNumConstraintRefs();
  for (int i = 0; i < numConstraints; ++i) {
    btTypedConstraint* constraint = collider->rigidBody->getConstraintRef(i);
    Engine::physics.dynamicsWorld->removeConstraint(constraint);
    delete constraint;
  }
}

void Player::update()
{
  linearVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
  angularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

  if(this->input->actionHeld("left") && this->input->actionHeld("right"))
  {
    linearVelocity.x = 0;
  }
  else if(this->input->actionHeld("left"))
  {
    linearVelocity.x = -speed;
    angularVelocity.z = speed;
  }
  else if(this->input->actionHeld("right"))
  {
    linearVelocity.x = speed;
    angularVelocity.z = -speed;
  }

  if(this->input->actionHeld("up") && this->input->actionHeld("down"))
  {
    linearVelocity.z = 0;
  }
  else if(this->input->actionHeld("up"))
  {
    linearVelocity.z = -speed;
    angularVelocity.x = -speed;
  }
  else if(this->input->actionHeld("down"))
  {
    linearVelocity.z = speed;
    angularVelocity.x = speed;
  }

  this->collider->rigidBody->setLinearVelocity(btVector3(linearVelocity.x, linearVelocity.y, linearVelocity.z));
  this->collider->rigidBody->setAngularVelocity(btVector3(angularVelocity.x, angularVelocity.y, angularVelocity.z));
}

void Player::setConstraint(glm::vec3 start, glm::vec3 end)
{
  btVector3 linearLower(start.x, start.y, start.z); // Set lower limit for linear motion (X, Y, Z)
  btVector3 linearUpper(end.x, end.y, end.z);   // Set upper limit for linear motion (X, Y, Z)

  btGeneric6DofConstraint* constraint = new btGeneric6DofConstraint(*collider->rigidBody, btTransform::getIdentity(), false);
  constraint->setLinearLowerLimit(linearLower);
  constraint->setLinearUpperLimit(linearUpper);

  // Add the constraint to the dynamics world
  Engine::physics.addConstraint(this->handle, constraint);
}
