#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>
#include "glm/gtx/string_cast.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
  glm::vec3 Color;

  const std::string toString() {
    return glm::to_string(Position);
  }
};

struct MeshTexture {
  std::string type;
  std::string path;
};

class ModelLoader {
  protected:
    std::string m_PathToFile;
    std::string m_Directory;
    std::vector<std::vector<Vertex> > m_Vertexes;
    std::vector<std::vector<unsigned int> > m_Indexes;
    std::vector<std::map<std::string, MeshTexture> > m_Textures;

  public:
    virtual ~ModelLoader() {};
    virtual void Load() {};

    inline const std::vector<std::vector<Vertex> > GetVertexes() const { return m_Vertexes; }
    inline const std::vector<std::vector<unsigned int> > GetIndexes() const { return m_Indexes; }
    inline const std::vector<std::map<std::string, MeshTexture> > GetTextures() const { return m_Textures; }
};
