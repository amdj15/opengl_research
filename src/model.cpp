#include "model.h"
#include "loaders/base_loader.h"
#include "loaders/assimp_loader.h"

#include <iostream>

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

Model::Model() {}

Model::Model(const std::string pathToFile):
  m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));
  m_Loader = new AssimpLoader(pathToFile);
}

Model::Model(const std::string pathToFile, const std::string loader):
  m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));

  if (loader == "base") {
    m_Loader = new BaseLoader(pathToFile);
  } else {
    m_Loader = new AssimpLoader(pathToFile);
  }
}

Model::~Model() {
  delete m_Loader;
}

void Model::Load() {
  m_Loader->Load();

  Mesh mesh(m_Loader->GetVertexes(), m_Loader->GetIndexes());

  m_Meshes.push_back(mesh);
}

