#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "glm/gtx/string_cast.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;

  const std::string toString() {
    return glm::to_string(Position);
  }
};

struct MeshTexture {
  unsigned int id;
  std::string type;
};

class ModelLoader {
  protected:
    std::string m_PathToFile;
    std::vector<std::vector<Vertex> > m_Vertexes;
    std::vector<std::vector<unsigned int> > m_Indexes;

  public:
    virtual ~ModelLoader() {};
    virtual void Load() {};

    inline const std::vector<std::vector<Vertex> > GetVertexes() const { return m_Vertexes; }
    inline const std::vector<std::vector<unsigned int> > GetIndexes() const { return m_Indexes; }
};
