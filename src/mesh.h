#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "vertex_array.h"
#include "index_buffer.h"

struct Vertex {
  glm::vec3 Position;
  // glm::vec3 Normal;
  // glm::vec2 TexCoords;
};

struct MeshTexture {
  unsigned int id;
  std::string type;
};

class Mesh {
    public:
      std::vector<Vertex> m_Vertices;
      std::vector<unsigned int> m_Indices;
      std::vector<MeshTexture> m_Textures;

      Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    private:
      VertexArray m_VAO;
      IndexBuffer m_IBO;

      void setupMesh();

    public:
      inline VertexArray GetVao() const {
        return m_VAO;
      }

      inline IndexBuffer GetIbo() const {
        return m_IBO;
      }
};

