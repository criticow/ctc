#include "light_system.hpp"
#include <core/engine.hpp>

void LightSystem::render()
{
  Shader& shader = Engine::resourceManager.getShader("default");
  shader.use();
  
  auto lightView = Engine::registry.view<Transform, Light>();
  for(auto [entity, transform, light] : lightView.each())
  {
    if(light.type == DIRECTIONAL)
    {
      glm::mat4 rotated = glm::mat4(1.0f);
      glm::mat4 rotationMatrix = glm::eulerAngleYXZ(glm::radians(transform.rotation.y), glm::radians(transform.rotation.x), glm::radians(transform.rotation.z));
      glm::vec3 direction = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)); // Use the forward vector

      shader.setFloat("light.direction", glm::normalize(direction));
      shader.setFloat("light.ambient", light.ambient);
      shader.setFloat("light.diffuse", light.diffuse);
      shader.setFloat("light.specular", light.specular);
    }
  }
}