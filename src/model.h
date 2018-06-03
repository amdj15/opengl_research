#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>
#include "mesh.h"

class Model {
  public:
    Model(const std::string pathToFile);

  private:
    std::vector<Mesh> m_Meshes;
    std::string m_PathToFile;
    std::string m_Directory;

    void processNode(const aiNode* node, const aiScene* scene);
    Mesh processMesh(const aiMesh* mesh);

  public:
    void Load();

    inline std::vector<Mesh> getMeshes() const {
      return m_Meshes;
    }
};
