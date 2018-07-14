#include "mesh.h"
#include "vertex_buffer_layout.h"
#include "vertex_buffer.h"
#include <vector>
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::map<std::string, MeshTexture> textures):
  m_Vertices(vertices),
  m_Indices(indices),
  m_MeshTextureStructs(textures)
{
  setupMesh();
}

Mesh::~Mesh() {
  for (std::map<std::string, Texture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); it++) {
    std::cout << "Delete texture " << it->second->GetRendererId() << std::endl;

    delete it->second;
  }
}

void Mesh::setupMesh() {
  m_IBO.SetData(&m_Indices[0], m_Indices.size());

  std::vector<float> vertexesData;

  for(int i = 0; i < m_Vertices.size(); i++) {
    vertexesData.push_back(m_Vertices[i].Position.x);
    vertexesData.push_back(m_Vertices[i].Position.y);
    vertexesData.push_back(m_Vertices[i].Position.z);

    vertexesData.push_back(m_Vertices[i].Normal.x);
    vertexesData.push_back(m_Vertices[i].Normal.y);
    vertexesData.push_back(m_Vertices[i].Normal.z);

    vertexesData.push_back(m_Vertices[i].TexCoords.x);
    vertexesData.push_back(m_Vertices[i].TexCoords.y);

    vertexesData.push_back(m_Vertices[i].Color.x);
    vertexesData.push_back(m_Vertices[i].Color.y);
    vertexesData.push_back(m_Vertices[i].Color.z);
  }

  VertexBuffer vbo(&vertexesData[0], sizeof(float) * vertexesData.size());

  VertexBufferLayout layout;
  layout.push(3);
  layout.push(3);
  layout.push(2);
  layout.push(3);

  m_VAO.addBuffer(vbo, layout);

  for (std::map<std::string, MeshTexture>::iterator it = m_MeshTextureStructs.begin(); it != m_MeshTextureStructs.end(); it++) {
    Texture *texture = new Texture(it->first);
    texture->bind(0);

    m_Textures[it->first] = texture;
  }

  vbo.unbind();
  m_VAO.unbind();
  m_IBO.unbind();
}
