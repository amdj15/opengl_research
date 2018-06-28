#pragma once

#include <string>
#include <vector>
#include <assimp/scene.h>
#include "mesh.h"
#include "loaders/model_loader.h"

class Model {
  public:
    Model();
    Model(const std::string pathToFile);
    Model(const std::string pathToFile, const std::string loader);
    ~Model();

  private:
    std::vector<Mesh> m_Meshes;
    std::string m_PathToFile;
    std::string m_Directory;
    ModelLoader* m_Loader;

  public:
    void Load();

    inline std::vector<Mesh> getMeshes() const {
      return m_Meshes;
    }
};
