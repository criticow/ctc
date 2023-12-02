#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h>

#include <resources/texture.hpp>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

struct Transform
{
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
};

enum ProjectionType
{
  ORTHOGRAPHIC,
  PERSPECTIVE
};

struct Projection
{
  bool active = false;
  ProjectionType type = PERSPECTIVE;
  float fov = 75.0f;
  float near = 0.05f;
  float far = 4000.0f;
};

struct Vertex
{
  glm::vec3 position;
  glm::vec2 uv;
  glm::vec3 normal;

  Vertex(void) = default;
  Vertex(const glm::vec3 position, const glm::vec2 uv, const glm::vec3 normal) :
    position(position), uv(uv), normal(normal) {}
  Vertex(const aiVector3D position, const aiVector2D uv, const aiVector3D normal) :
    position(position.x, position.y, position.z), uv(uv.x, uv.y), normal(normal.x, normal.y, normal.z) {}
};

struct Mesh
{
  std::string name;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
};

struct Material
{
  Texture2D diffuseTexture;
  glm::vec3 diffuseColor = glm::vec3(0.207f);
  glm::vec3 specularColor = glm::vec3(0.5f);
  float shininess = 250.0f;
};

enum LightType
{
  DIRECTIONAL,
  POINT
};

struct Light
{
  LightType type = DIRECTIONAL;
  glm::vec3 color = glm::vec3(1.0f);
  glm::vec3 diffuse = color * glm::vec3(1.0f);
  glm::vec3 ambient = diffuse * glm::vec3(0.57f);
  glm::vec3 specular = glm::vec3(1.0f);
};

struct Collider
{
  enum Type
  {
    BOX,
    SPHERE,
    CAPSULE
  };

  btCollisionShape* shape = nullptr;
  btRigidBody* rigidBody = nullptr;
  btMotionState* motionState = nullptr;
  Collider(Type type, const Transform& transform, float mass = 0.0f, glm::vec3 inertia = glm::vec3(0.0f));
};

struct GhostTrigger
{
  btGhostObject* ghostObject;
  GhostTrigger(const Transform& transform, glm::vec3 size = glm::vec3(1.0f));
};