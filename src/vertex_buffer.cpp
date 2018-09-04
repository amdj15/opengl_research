#include "vertex_buffer.h"

#include "graphic/api/renderer.h"
#include "devices/opengl/common.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
  GLCall(glGenBuffers(1, &m_RendererId));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

