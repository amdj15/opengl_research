#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>
#include <iostream>

Model::Model(const std::string pathToFile): m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));
}

void Model::Load() {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(m_PathToFile, aiProcess_Triangulate);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    return;
  }

  processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode* node, const aiScene* scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    m_Meshes.push_back(processMesh(mesh));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i ++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(const aiMesh* mesh) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  std::cout << "vertices number: " << mesh->mNumVertices << std::endl;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 position;

    position.x = mesh->mVertices[i].x;
    position.y = mesh->mVertices[i].y;
    position.z = mesh->mVertices[i].z;

    vertex.Position = position;

    vertices.push_back(vertex);
  }

  for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for(unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  return Mesh(vertices, indices);
}
