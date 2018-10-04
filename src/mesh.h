#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "graphic/api/vertex_array.h"
#include "graphic/api/index_buffer.h"
#include "graphic/api/texture.h"
#include "loaders/model_loader.h"

class Mesh {
  public:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::map<std::string, MeshTexture> m_MeshTextureStructs;
    std::map<std::string, Graphic::Texture*> m_Textures;
    MeshMaterials m_Materials;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::map<std::string, MeshTexture> meshTextureStructs);
    ~Mesh();

  private:
    Graphic::VertexArray *m_VAO;
    Graphic::IndexBuffer *m_IBO;

    void setupMesh();

  public:
    inline Graphic::VertexArray* GetVao() const { return m_VAO; }
    inline Graphic::IndexBuffer* GetIbo() const { return m_IBO; }
    inline const std::map<std::string, Graphic::Texture*> GetTextures() const { return m_Textures; }
};

