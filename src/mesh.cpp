#include "mesh.h"
#include "vertex_buffer_layout.h"
#include "vertex_buffer.h"
#include <vector>

#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices):
  m_Vertices(vertices),
  m_Indices(indices) {
    setupMesh();
  }

void Mesh::setupMesh() {
  m_IBO.SetData(&m_Indices[0], m_Indices.size());

  std::vector<float> vertexesData;

  for(int i = 0; i < m_Vertices.size(); i++) {
    vertexesData.push_back(m_Vertices[i].Position.x);
    vertexesData.push_back(m_Vertices[i].Position.y);
    vertexesData.push_back(m_Vertices[i].Position.z);
  }

  VertexBuffer vbo(&vertexesData[0], sizeof(float) * vertexesData.size());

  VertexBufferLayout layout;
  layout.push(3);

  m_VAO.addBuffer(vbo, layout);

  vbo.unbind();
  m_VAO.unbind();
  m_IBO.unbind();
}
