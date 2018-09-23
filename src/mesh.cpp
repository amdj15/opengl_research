#include "mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::map<std::string, MeshTexture> textures):
  m_Vertices(vertices),
  m_Indices(indices),
  m_MeshTextureStructs(textures)
{
  this->m_VAO = Graphic::VertexArray::Create();
  this->m_IBO = new IndexBuffer();

  setupMesh();
}

Mesh::~Mesh() {
  for (std::map<std::string, Texture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); it++) {
    std::cout << "Delete texture " << it->second->GetRendererId() << std::endl;

    delete it->second;
  }

  delete m_VAO;
  delete m_IBO;
}

void Mesh::setupMesh() {
  m_IBO->SetData(&m_Indices[0], m_Indices.size());

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

    vertexesData.push_back(m_Vertices[i].Tangent.x);
    vertexesData.push_back(m_Vertices[i].Tangent.y);
    vertexesData.push_back(m_Vertices[i].Tangent.z);
  }

  Graphic::VertexBuffer* vbo = Graphic::VertexBuffer::Create(&vertexesData[0], sizeof(float) * vertexesData.size());

  VertexBufferLayout layout;
  layout.Push(3);
  layout.Push(3);
  layout.Push(2);
  layout.Push(3);

  m_VAO->AddBuffer(*vbo, layout);

  for (std::map<std::string, MeshTexture>::iterator it = m_MeshTextureStructs.begin(); it != m_MeshTextureStructs.end(); it++) {
    Texture *texture = new Texture(it->first);
    m_Textures[it->second.type] = texture;
  }

  m_VAO->Unbind();
  m_IBO->unbind();

  delete vbo;
}
