#include "physics.hpp"

Physics::Physics()
{
  LOGGER_DEBUG("Creating Physics");
  this->collisionConfiguration = new btDefaultCollisionConfiguration();
  this-> dynamicsWorld = new btDiscreteDynamicsWorld(
    new btCollisionDispatcher(collisionConfiguration),
    new btDbvtBroadphase(),
    new btSequentialImpulseConstraintSolver(),
    collisionConfiguration
  );
  this->dynamicsWorld->setGravity(btVector3(0.0f, -9.8f, 0.0f));

  this->dynamicsWorld->setDebugDrawer(&this->drawer);
  this->dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
  // this->dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawContactPoints);
}

void Physics::addRigidBody(entt::entity entity, btRigidBody *rigidBody)
{
  // If the rigid body is already in the map, remove it first
  if(this->rigidBodies.find(entity) != this->rigidBodies.end())
  {
    this->removeRigidBody(entity);
  }

  this->dynamicsWorld->addRigidBody(rigidBody);
  this->rigidBodies[entity] = rigidBody;
}

void Physics::addConstraint(entt::entity entity, btGeneric6DofConstraint *constraint)
{
  // If there is already a constraint for this entity, remove it before adding a new one
  if(this->constraints.find(entity) != this->constraints.end())
  {
    this->removeConstraint(entity);
  }

  this->dynamicsWorld->addConstraint(constraint, true);
  this->constraints[entity] = constraint;
}

void Physics::removeConstraint(entt::entity entity)
{
  // If the constraint is not in the map, just leave
  if(this->constraints.find(entity) == this->constraints.end())
  {
    return;
  }

  btGeneric6DofConstraint* constraint = this->constraints[entity];
  this->dynamicsWorld->removeConstraint(constraint);
  this->constraints.erase(entity);
  delete constraint;
}

void Physics::removeRigidBody(entt::entity entity)
{
  // If the rigid body is not in the map, just leave
  if(this->rigidBodies.find(entity) == this->rigidBodies.end())
  {
    return;
  }

  btRigidBody *rigidBody = this->rigidBodies[entity];

  this->dynamicsWorld->removeRigidBody(rigidBody);
  this->rigidBodies.erase(entity);

  delete rigidBody->getMotionState();
  // Collision shapes are not being reused, each rigid body has his own 
  // if in the future shapes would be reused i cannot do this
  delete rigidBody->getCollisionShape();
  delete rigidBody;
}

void Physics::addGhostTrigger(entt::entity entity, btGhostObject *ghostObject)
{
  if(this->ghostObjects.find(entity) != this->ghostObjects.end())
  {
    this->removeGhostTrigger(entity);
  }

  this->dynamicsWorld->addCollisionObject(ghostObject, btBroadphaseProxy::SensorTrigger, btBroadphaseProxy::AllFilter);
  this->ghostObjects[entity] = ghostObject;
}

void Physics::removeGhostTrigger(entt::entity entity)
{
  if(this->ghostObjects.find(entity) == this->ghostObjects.end())
  {
    return;
  }

  btGhostObject* ghostObject = this->ghostObjects[entity];

  this->dynamicsWorld->removeCollisionObject(ghostObject);
  this->ghostObjects.erase(entity);
  delete ghostObject->getCollisionShape();
  delete ghostObject;
}

void Physics::stepSimulation(float deltaTime)
{
  this->dynamicsWorld->stepSimulation(deltaTime);
}

void Physics::debugDraw()
{
  this->dynamicsWorld->debugDrawWorld();
  this->drawer.lineRenderer.render();
  this->drawer.lineRenderer.clear();
}

bool Physics::isColliding(btRigidBody *bodyA, btRigidBody *bodyB)
{
  this->dynamicsWorld->performDiscreteCollisionDetection();

  int numManifolds = this->dynamicsWorld->getDispatcher()->getNumManifolds();
  for (int i = 0; i < numManifolds; i++) {
    btPersistentManifold* contactManifold = this->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* body0 = contactManifold->getBody0();
    const btCollisionObject* body1 = contactManifold->getBody1();

    if ((body0 == bodyA && body1 == bodyB) || (body0 == bodyB && body1 == bodyA)) {
      bool isBodyABody0 = body0 == bodyA;
      return true;
    }
  }

  return false;
}

bool Physics::isOnGround(btRigidBody *body)
{
  this->dynamicsWorld->performDiscreteCollisionDetection();

  int numManifolds = this->dynamicsWorld->getDispatcher()->getNumManifolds();
  for(int i = 0; i < numManifolds; i++)
  {
    btPersistentManifold* contactManifold = this->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* body0 = contactManifold->getBody0();
    const btCollisionObject* body1 = contactManifold->getBody1();

    if(body0 == body || body1 == body)
    {
      int numContacts = contactManifold->getNumContacts();

      for(int j = 0; j < numContacts; j++)
      {
        const btManifoldPoint& point = contactManifold->getContactPoint(j);
        const btVector3& normal = point.m_normalWorldOnB;
        float yNormal = body0 == body ? normal.y() : -normal.y();

        if(yNormal > 0.0f)
        {
          return true;
        }
      }
    }
  }

  return false;
}

btCollisionWorld::ClosestRayResultCallback Physics::raycast(btVector3 start, btVector3 end)
{
  btCollisionWorld::ClosestRayResultCallback callback(start, end);
  this->dynamicsWorld->rayTest(start, end, callback);
  return callback;
}

Physics::~Physics()
{
  LOGGER_DEBUG("Destroying Ghost Objects");
  for(auto [entity, ghostObject] : this->ghostObjects)
  {
    this->dynamicsWorld->removeCollisionObject(ghostObject);
    delete ghostObject->getCollisionShape();
    delete ghostObject;
  }

  LOGGER_DEBUG("Destroying Rigid Bodies");
  // Cleanup Rigid Bodies
  for(auto [entity, rigidBody] : this->rigidBodies)
  {
    this->dynamicsWorld->removeRigidBody(rigidBody);
    delete rigidBody->getMotionState();
    delete rigidBody->getCollisionShape();
    delete rigidBody;
  }

  // Cleanup configuration stuff
  LOGGER_DEBUG("Destroying Physics");
  delete this->dynamicsWorld->getBroadphase();
  delete this->dynamicsWorld->getDispatcher();
  delete this->dynamicsWorld->getConstraintSolver();
  delete this->dynamicsWorld;
  delete this->collisionConfiguration;
}
