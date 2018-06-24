#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

#include <fstream>
#include <sstream>
#include <algorithm>

static std::vector<std::string> splitString(std::string str, const char delimeter) {
  char *token = std::strtok(&str[0], &delimeter);
  std::vector<std::string> tokens;

  while(token != NULL) {
    tokens.push_back(token);
    token = std::strtok(NULL, &delimeter);
  }

  delete token;
  return tokens;
}

template <typename T>
static std::pair<bool, int> findInVector(const std::vector<T> &vecOfElements, const T &element) {
	std::pair<bool, int> result;

	// Find given element in vector
	auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);

	if (it != vecOfElements.end()) {
		result.second = distance(vecOfElements.begin(), it);
		result.first = true;
	} else {
		result.first = false;
		result.second = -1;
	}

	return result;
}

static void processVertex(
  std::vector<int> &loadedCoordinates,
  std::vector<Vertex> &outVertexes,
  std::vector<unsigned int> &indexes,
  std::vector<glm::vec3> &coordinates,
  std::vector<glm::vec3> &normals,
  std::string rawPoint
) {
  int vertexIndex = -1;
  int textureIndex = -1;
  int normalIndex = -1;

  int slashesCnt = std::count(rawPoint.begin(), rawPoint.end(), '/');
  std::vector<std::string> faceIndexes = splitString(rawPoint, '/');

  switch(slashesCnt) {
    case 0:
      vertexIndex = std::atoi(rawPoint.c_str());
      break;
    case 1:
      vertexIndex = std::atoi(faceIndexes[0].c_str());
      textureIndex = std::atoi(faceIndexes[1].c_str());
      break;
    case 2:
      vertexIndex = std::atoi(faceIndexes[0].c_str());

      if (faceIndexes.size() == 3) {
        textureIndex = std::atoi(faceIndexes[1].c_str());
        normalIndex = std::atoi(faceIndexes[2].c_str());
      } else {
        normalIndex = std::atoi(faceIndexes[1].c_str());
      }

      break;
  }

  vertexIndex--;
  normalIndex--;

  Vertex vertex;
  vertex.Position = coordinates[vertexIndex];
  vertex.Normal = glm::vec3(0.0f);

  if (normalIndex > -1) {
    vertex.Normal = normals[normalIndex];
  }

  std::pair<bool, int> presenceInVector = findInVector(loadedCoordinates, vertexIndex);
  if (!presenceInVector.first) {
    loadedCoordinates.push_back(vertexIndex);
    outVertexes.push_back(vertex);
  }

  indexes.push_back(vertexIndex);
}

std::ostream& operator<<(std::ostream& os, const Mesh &m) {
  os << "Indexes size: " << m.m_Indices.size() << std::endl;
  os << "Indexes array: {" << std::endl;

  for (unsigned int i = 0; i < m.m_Indices.size(); i++) {
    os << m.m_Indices[i] << ", ";
  }

  os << "\n}" << std::endl;
  os << "Vetexes: {" << std::endl;

  for (unsigned int i = 0; i < m.m_Vertices.size(); i++) {
    os << "  " << m.m_Vertices[i].Position.x << ", "
       << m.m_Vertices[i].Position.y << ", "
       << m.m_Vertices[i].Position.z;

    os << std::endl;
  }

  os << "}" << std::endl;

  return os;
}

Model::Model(const std::string pathToFile): m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));
}

void Model::Load() {
  std::ifstream file(m_PathToFile);

  std::string line;
  std::vector<glm::vec3> coordinates;
  std::vector<glm::vec3> normals;
  std::vector<unsigned int> indexes;
  std::vector<std::string> faces;

  std::vector<Vertex> outVertexes;

  while(std::getline(file, line)) {
    std::istringstream iss(line);

    switch(line[0]) {
      case 'v':
        if (line[1] == ' ')
          this->parseCoordinates(coordinates, line);

        if (line[1] == 'n')
          this->parseCoordinates(normals, line);

        break;
      case 'f':
        faces.push_back(line.substr(2));
        break;
    }
  }

  std::vector<int> loadedCoordinates;
  std::vector<int> loadedNormals;

  for (unsigned int i = 0; i < faces.size(); i++) {
    std::vector<std::string> faceIndexes = splitString(faces[i], ' ');

    // std::reverse(faceIndexes.begin(), faceIndexes.end());

    for (int j = 0; j < faceIndexes.size(); j++) {
      processVertex(
        loadedCoordinates,
        outVertexes,
        indexes,
        coordinates,
        normals,
        faceIndexes[j]
      );
    }
  }

  // exit(0);

  Mesh mesh(outVertexes, indexes);

  m_Meshes.push_back(mesh);
}

void Model::parseCoordinates(std::vector<glm::vec3> &vertices, std::string line) {
  std::vector<std::string> tokens = splitString(line, ' ');

  glm::vec3 position;

  position.x = std::atof(&tokens[1][0]);
  position.y = std::atof(&tokens[2][0]);
  position.z = std::atof(&tokens[3][0]);

  vertices.push_back(position);
}






























void Model::Assimp() {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(m_PathToFile, aiProcess_Triangulate | aiProcess_FlipUVs);

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

    vertices.push_back(vertex);
  }

  for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for(unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  Mesh msh(vertices, indices);

  return msh;
}
