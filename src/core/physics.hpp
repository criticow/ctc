#pragma once

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <unordered_map>
#include <entt/entt.hpp>

#include <ecs/components/components.hpp>
#include <core/debug_drawer.hpp>

class Physics
{
  public:
  Physics();
  ~Physics();
  void addRigidBody(entt::entity entity, btRigidBody* rigidBody);
  void addConstraint(entt::entity entity, btGeneric6DofConstraint* constraint);
  void removeConstraint(entt::entity entity);
  void removeRigidBody(entt::entity entity);
  void addGhostTrigger(entt::entity entity, btGhostObject* ghostObject);
  void removeGhostTrigger(entt::entity entity);
  void stepSimulation(float deltaTime);
  void debugDraw();
  bool isColliding(btRigidBody* bodyA, btRigidBody* bodyB);
  bool isOnGround(btRigidBody* body);

  btCollisionWorld::ClosestRayResultCallback raycast(btVector3 start, btVector3 end);

  btDiscreteDynamicsWorld* dynamicsWorld = nullptr;
  DebugDrawer drawer;
  private:
  btDefaultCollisionConfiguration* collisionConfiguration = nullptr;

  std::unordered_map<entt::entity, btRigidBody*> rigidBodies;
  std::unordered_map<entt::entity, btGeneric6DofConstraint*> constraints;
  std::unordered_map<entt::entity, btGhostObject*> ghostObjects;
};