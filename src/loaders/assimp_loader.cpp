#include "assimp_loader.h"
#include <iostream>

AssimpLoader::AssimpLoader(std::string pathToFile, std::string directory) {
  m_PathToFile = pathToFile;
  m_Directory = directory;
}

AssimpLoader::~AssimpLoader() {}

void AssimpLoader::Load() {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(m_PathToFile, aiProcess_Triangulate |
                                                         // aiProcess_FlipUVs |
                                                         aiProcess_CalcTangentSpace |
                                                         aiProcess_GenNormals |
                                                         aiProcess_JoinIdenticalVertices |
                                                         aiProcess_OptimizeGraph |
                                                         aiProcess_OptimizeMeshes |
                                                         aiProcess_FindInstances
                                          );

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    return;
  }

  this->processNode(scene->mRootNode, scene);
}

void AssimpLoader::processNode(const aiNode* node, const aiScene* scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    this->processMesh(mesh, scene);
  }

  for (unsigned int i = 0; i < node->mNumChildren; i ++) {
    this->processNode(node->mChildren[i], scene);
  }
}

void AssimpLoader::processMesh(const aiMesh* mesh, const aiScene *scene) {
  std::vector<unsigned int> indexes;
  std::vector<Vertex> vertexes;
  std::map<std::string, MeshTexture> textures;

  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;

    glm::vec3 position;
    position.x = mesh->mVertices[i].x;
    position.y = mesh->mVertices[i].y;
    position.z = mesh->mVertices[i].z;
    vertex.Position = position;

    glm::vec3 normal;
    normal.x = mesh->mNormals[i].x;
    normal.y = mesh->mNormals[i].y;
    normal.z = mesh->mNormals[i].z;
    vertex.Normal = normal;

    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = vec;
    } else {
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    }

    this->loadTexture(material, aiTextureType_DIFFUSE, "texture_diffuse", textures, 0);
    this->loadTexture(material, aiTextureType_SPECULAR, "texture_specular", textures, 1);
    bool haveNormalMap = this->loadTexture(material, aiTextureType_HEIGHT, "texture_normal", textures, 2);

    // tangent
    glm::vec3 tangent;

    if (haveNormalMap) {
      tangent.x = mesh->mTangents[i].x;
      tangent.y = mesh->mTangents[i].y;
      tangent.z = mesh->mTangents[i].z;
    }

    vertex.Tangent = tangent;

    vertexes.push_back(vertex);
  }

  for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for(unsigned int j = 0; j < face.mNumIndices; j++) {
      indexes.push_back(face.mIndices[j]);
    }
  }

  m_Vertexes.push_back(vertexes);
  m_Indexes.push_back(indexes);
  m_Textures.push_back(textures);
  m_Materials.push_back(this->processMaterials(material));

  std::cout << "vertices number: " << mesh->mNumVertices << ", indexes: " << indexes.size() << std::endl;
}

bool AssimpLoader::loadTexture(const aiMaterial *material, aiTextureType type, std::string typeName, std::map<std::string, MeshTexture> &textures, unsigned int slot) {
  for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
    aiString path;
    material->GetTexture(type, i, &path);

    std::string fullpath = m_Directory + "/" + path.C_Str();

    MeshTexture texture;
    texture.path = fullpath;
    texture.type = typeName;
    texture.slot = slot;

    textures[fullpath] = texture;
  }

  return material->GetTextureCount(type) > 0;
}

MeshMaterials AssimpLoader::processMaterials(aiMaterial *material) {
  MeshMaterials meshMaterials;

  material->Get(AI_MATKEY_SHININESS, meshMaterials.shininess);
  material->Get(AI_MATKEY_SHININESS_STRENGTH, meshMaterials.shininessStrength);

  return meshMaterials;
}
