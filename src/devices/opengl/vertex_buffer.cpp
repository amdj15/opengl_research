#include "common.h"
#include "vertex_buffer.h"

using namespace Devices;
using namespace OpenGL;

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
