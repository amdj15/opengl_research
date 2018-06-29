#include "assimp_loader.h"
#include <iostream>

AssimpLoader::AssimpLoader(std::string pathToFile) {
  m_PathToFile = pathToFile;
}

AssimpLoader::~AssimpLoader() {}

void AssimpLoader::Load() {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(m_PathToFile, aiProcess_Triangulate |
                                                         aiProcess_FlipUVs |
                                                         aiProcess_GenNormals |
                                                         aiProcess_JoinIdenticalVertices
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
    this->processMesh(mesh);
  }

  for (unsigned int i = 0; i < node->mNumChildren; i ++) {
    this->processNode(node->mChildren[i], scene);
  }
}

void AssimpLoader::processMesh(const aiMesh* mesh) {
  std::vector<unsigned int> indexes;
  std::vector<Vertex> vertexes;

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

  std::cout << "vertices number: " << mesh->mNumVertices << ", indexes: " << indexes.size() << std::endl;
}
