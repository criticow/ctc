#include "mesh_system.hpp"
#include <core/engine.hpp>

void MeshSystem::render()
{
  Shader& shader = Engine::resourceManager.getShader("default");
  shader.use();

  auto renderView = Engine::registry.view<Transform, Mesh, Material>();
  for(auto [entity, transform, mesh, material] : renderView.each())
  {
    if(!Engine::resourceManager.hasResource<RenderObject>(mesh.name))
    {
      Engine::resourceManager.setRenderObject(mesh.name, mesh.vertices, mesh.indices);
    }

    RenderObject &renderObject = Engine::resourceManager.getRenderObject(mesh.name);
    renderObject.bind();

    if(material.diffuseTexture)
    {
      material.diffuseTexture.bind();
      shader.setInt("material.diffuseTexture", 0);
    }
    else
    {
      shader.setFloat("material.diffuseColor", material.diffuseColor);
    }

    shader.setInt("material.hasTexture", material.diffuseTexture);
    shader.setMatrix("projectionView", Engine::cameraSystem.projectionMatrix * Engine::cameraSystem.viewMatrix);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform.position);
    // model = glm::toMat4(glm::quat(transform.rotation));
    model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, transform.scale);

    shader.setMatrix("model", model);

    renderObject.render(mesh.indices.size());
  }
}