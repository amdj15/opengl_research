#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

#include <fstream>
#include <sstream>

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
static std::pair<bool, int> findInVector(const std::vector<T> &vecOfElements, const T &element)
{
	std::pair<bool, int> result;

	// Find given element in vector
	auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);

	if (it != vecOfElements.end())
	{
		result.second = distance(vecOfElements.begin(), it);
		result.first = true;
	}
	else
	{
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
  int faceId
  ) {
  std::pair<bool, int> presenceInVector = findInVector(loadedCoordinates, faceId);

  if (!presenceInVector.first) {
    loadedCoordinates.push_back(faceId);

    Vertex vertex;
    vertex.Position = coordinates[faceId];
    outVertexes.push_back(vertex);
  }

  indexes.push_back(faceId);
}

Model::Model(const std::string pathToFile): m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));
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
    os << "  " <<m.m_Vertices[i].Position.x << ", "
       << m.m_Vertices[i].Position.y << ", "
       << m.m_Vertices[i].Position.z;

    os << std::endl;
  }

  os << "}" << std::endl;

  return os;
}

void Model::Load() {
  std::ifstream file(m_PathToFile);

  std::string line;
  std::vector<glm::vec3> coordinates;
  std::vector<unsigned int> indexes;
  std::vector<std::string> faces;

  std::vector<Vertex> outVertexes;

  while(std::getline(file, line)) {
    std::istringstream iss(line);

    switch(line[0]) {
      case 'v':
        if (line[1] == ' ')
          parseCoordinates(coordinates, line);
        break;
      case 'f':
        faces.push_back(line.substr(2));
        break;
    }
  }

  std::vector<int> loadedCoordinates;

  for (unsigned int i = 0; i < faces.size(); i++) {
    std::vector<std::string> faceIndexes = splitString(faces[i], ' ');

    int faceIndex0 = std::atoi(&faceIndexes[0][0]) - 1;
    int faceIndex1 = std::atoi(&faceIndexes[1][0]) - 1;
    int faceIndex2 = std::atoi(&faceIndexes[2][0]) - 1;

    processVertex(loadedCoordinates, outVertexes, indexes, coordinates, faceIndex2);
    processVertex(loadedCoordinates, outVertexes, indexes, coordinates, faceIndex1);
    processVertex(loadedCoordinates, outVertexes, indexes, coordinates, faceIndex0);
  }

  Mesh mesh(outVertexes, indexes);

  // std::cout << mesh << std::endl;
  // exit(0);

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

    // glm::vec3 normal;
    // normal.x = mesh->mNormals[i].x;
    // normal.y = mesh->mNormals[i].y;
    // normal.z = mesh->mNormals[i].z;
    // vertex.Normal = normal;

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

  // std::cout << msh << std::endl;
  // exit(0);

  return msh;
}
