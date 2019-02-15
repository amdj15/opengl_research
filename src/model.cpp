#include "model.h"
#include "loaders/assimp_loader.h"
#include "utils/logger.h"

Model::Model() {}

Model::Model(const std::string &pathToFile): m_PathToFile(pathToFile) {
  m_Directory = pathToFile.substr(0, pathToFile.find_last_of('/'));
  m_Loader = new AssimpLoader(pathToFile, m_Directory);
}

Model::~Model() {
  delete m_Loader;

  LOG_DEBUG("Delete model {}", m_PathToFile);

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

  LOG_DEBUG("Model has {} meshses", m_Meshes.size());
}

