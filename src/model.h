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
    void Assimp();

    inline std::vector<Mesh> getMeshes() const {
      return m_Meshes;
    }

  private:
    void parseCoordinates(std::vector<glm::vec3> &vertices, std::string line);
    void parseFace(
      std::vector<unsigned int> &indexes,
      std::vector<Vertex> &outVertexes,
      const std::string &line
    );
};
