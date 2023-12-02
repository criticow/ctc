#include "model.hpp"

Model::Model(const char *path)
{
  this->loadModel(path);
}

void Model::loadModel(const char* path)
{
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  ASSERT(!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode, "Could not load model: {}", path);
  ASSERT(scene->mRootNode->mNumMeshes == 0, "Model was not exported correctly: {}", path);

  aiMesh *mesh = scene->mMeshes[scene->mRootNode->mMeshes[0]];
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  // std::ostringstream sstream;
  for(int i = 0; i < mesh->mNumVertices; i++)
  {
    aiVector2D uv(0.0f);
    if(mesh->mTextureCoords[0])
      uv.x = mesh->mTextureCoords[0][i].x;
      uv.y = mesh->mTextureCoords[0][i].y;

    vertices.emplace_back(mesh->mVertices[i], uv, mesh->mNormals[i]);
    // sstream << "{glm::vec3" << vertices[i].position << ", glm::vec2" << vertices[i].uv << ", glm::vec3" << vertices[i].normal << "}," << "\n";
  }

  // std::cout << sstream.str() << std::endl;
  // sstream.clear();

  for(int i = 0; i < mesh->mNumFaces; i++)
  {
    for(int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
    {
      indices.push_back(mesh->mFaces[i].mIndices[j]);
      // sstream << mesh->mFaces[i].mIndices[j] << ", ";
    }
  }

  // std::cout << sstream.str() << std::endl;

  this->mesh = Mesh(mesh->mName.C_Str(), std::move(vertices), std::move(indices));

  this->material.specularColor = glm::vec3(0.5f);

  aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
  if(mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    aiString str;
    mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
    std::string path = str.C_Str();
    path = path.substr(path.find_last_of("/") + 1);
    path = "data/textures/" + path;
    this->material.diffuseTexture = Texture2D(path.c_str());
  }

  material.diffuseColor = glm::vec3(0.207f);
  material.specularColor = glm::vec3(0.5f);
  material.shininess = 250.0f;

  importer.FreeScene();
}