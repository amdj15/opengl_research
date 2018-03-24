#include <GL/glew.h>
#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout(): m_Stride(0) {}
VertexBufferLayout::~VertexBufferLayout(){}

void VertexBufferLayout::push(unsigned int count) {
  m_Elements.push_back({ GL_FLOAT, count });
  m_Stride += sizeof(count) * count;
}
