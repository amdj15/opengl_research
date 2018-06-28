#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct MeshTexture {
  unsigned int id;
  std::string type;
};

class ModelLoader {
  protected:
    std::string m_PathToFile;
    std::vector<Vertex> m_Vertexes;
    std::vector<unsigned int> m_Indexes;

  public:
    virtual ~ModelLoader() {};
    virtual void Load() {};

    inline const std::vector<Vertex> GetVertexes() const { return m_Vertexes; }
    inline const std::vector<unsigned int> GetIndexes() const { return m_Indexes; }
};
