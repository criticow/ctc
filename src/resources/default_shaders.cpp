#include "default_shaders.hpp"

Shader shaders::defaultShader()
{
  const char *vsData = R"(
    #version 460 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec2 uv;
    layout (location = 2) in vec3 normal;

    uniform mat4 projectionView;
    uniform mat4 model;

    out VS_OUT
    {
      vec2 uv;
      vec3 fragPos;
      vec3 normal;
    } vs_out;

    void main()
    {
      vs_out.uv       = uv;
      vs_out.fragPos  = vec3(model * vec4(position, 1.0));
      vs_out.normal   = mat3(transpose(inverse(model))) * normal;

      gl_Position     = projectionView * vec4(vs_out.fragPos, 1.0);
    }
  )";

  const char *fsData = R"(
    #version 460 core
    out vec4 fragColor;

    in VS_OUT
    {
      vec2 uv;
      vec3 fragPos;
      vec3 normal;
    } fs_in;

    struct Material
    {
      sampler2D diffuseTexture;
      vec3 diffuseColor;
      vec3 specular;
      float shininess;

      bool hasTexture;
    };

    struct Light
    {
      vec3 direction;

      vec3 ambient;
      vec3 diffuse;
      vec3 specular;
    };

    uniform vec3 viewPos;
    uniform Material material;
    uniform Light light;

    void main()
    {
      vec3 diffuseColor;

      if (material.hasTexture) {
        diffuseColor = texture(material.diffuseTexture, fs_in.uv).rgb;
      } else {
        diffuseColor = material.diffuseColor;
      }

      // AMBIENT

      vec3 ambient    = light.ambient * diffuseColor;

      // DIFFUSE

      vec3 norm       = normalize(fs_in.normal);
      vec3 lightDir   = normalize(-light.direction);
      float diff      = max(dot(norm, lightDir), 0.0);
      vec3 diffuse    = light.diffuse * (diff * diffuseColor);

      // SPECULAR

      vec3 viewDir    = normalize(viewPos - fs_in.fragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 specular   = light.specular * (spec * material.specular);

      vec3 result     = ambient + diffuse + specular;

      fragColor       = vec4(result, 1.0);
    }
  )";

  return Shader(vsData, fsData);
}

Shader shaders::lineShader()
{
  const char* vsData = R"(
    #version 460 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    uniform mat4 projectionView;
    out vec3 lineColor;

    void main()
    {
      gl_Position = projectionView * vec4(position, 1.0);
      lineColor = color;
    }
  )";

  const char* fsData = R"(
    #version 460 core
    out vec4 fragColor;
    in vec3 lineColor;

    void main()
    {
      fragColor = vec4(lineColor, 1.0);
    }
  )";

  return Shader(vsData, fsData);
}
