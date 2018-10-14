#include "model.h"
#include "loaders/assimp_loader.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Mesh &m) {
  os << "Indexes size: " << m.m_Indices.size() << std::endl;
  os << "Vertexes size: " << m.m_Vertices.size() << std::endl;

  os << "Indexes array: {" << std::endl;

  for (unsigned int i = 0; i < m.m_Indices.size(); i++) {
    os << "  " << m.m_Indices[i] << ", ";
  }

  os << "\n}" << std::endl;
  os << "Vetexes: {" << std::endl;

  for (unsigned int i = 0; i < m.m_Vertices.size(); i++) {
    os << "  " << m.m_Vertices[i].Position.x << ", "
       << m.m_Vertices[i].Position.y << ", "
       << m.m_Vertices[i].Position.z << ", "
       << m.m_Vertices[i].Normal.x << ", "
       << m.m_Vertices[i].Normal.y << ", "
       << m.m_Vertices[i].Normal.z;

    os << std::endl;
  }

  os << "}" << std::endl;

  return os;
}

Model::Model() {}

Model::Model(const std::string &pathToFile): m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));
  m_Loader = new AssimpLoader(pathToFile, m_Directory);
}

Model::~Model() {
  delete m_Loader;

  std::cout << "Delete model " << m_PathToFile << std::endl;

  for (unsigned int i = 0; i < m_Meshes.size(); i++) {
    delete m_Meshes[i];
  }
}

void Model::Load() {
  m_Loader->Load();

  std::vector<std::vector<Vertex> > vertexes = m_Loader->GetVertexes();
  std::vector<std::vector<unsigned int> > indexes = m_Loader->GetIndexes();
  std::vector<std::map<std::string, MeshTexture> > textures = m_Loader->GetTextures();
  std::vector<MeshMaterials> materials = m_Loader->GetMaterials();
  std::size_t cnt = vertexes.size();

  for (unsigned int i = 0; i < cnt; i++) {
    Mesh *mesh = new Mesh(vertexes[i], indexes[i], textures[i]);
    mesh->m_Materials = materials[i];

    m_Meshes.push_back(mesh);
  }

  std::cout << "Model has " << m_Meshes.size() << " meshses" << std::endl;
}

