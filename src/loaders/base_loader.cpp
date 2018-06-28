#include "base_loader.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <glm/glm.hpp>

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

BaseLoader::BaseLoader(std::string pathToFile) {
  m_PathToFile = pathToFile;
}

BaseLoader::~BaseLoader() {}

void BaseLoader::Load() {
  std::ifstream file(m_PathToFile);

  std::string line;
  std::vector<glm::vec3> coordinates;
  std::vector<glm::vec3> normals;
  std::vector<std::string> faces;

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

  for (unsigned int i = 0; i < faces.size(); i++) {
    std::vector<std::string> faceIndexes = splitString(faces[i], ' ');

    for (int j = 0; j < faceIndexes.size(); j++) {
      this->processVertex(
        coordinates,
        normals,
        faceIndexes[j]
      );
    }
  }
}

void BaseLoader::processVertex(
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

  std::pair<bool, int> presenceInVector = findInVector(m_LoadedCoordinates, vertexIndex);

  if (!presenceInVector.first) {
    m_LoadedCoordinates.push_back(vertexIndex);
    m_Vertexes.push_back(vertex);
  }

  m_Indexes.push_back(vertexIndex);
}

void BaseLoader::parseCoordinates(std::vector<glm::vec3> &vertices, std::string line) {
  std::vector<std::string> tokens = splitString(line, ' ');

  glm::vec3 position;

  position.x = std::atof(&tokens[1][0]);
  position.y = std::atof(&tokens[2][0]);
  position.z = std::atof(&tokens[3][0]);

  vertices.push_back(position);
}

