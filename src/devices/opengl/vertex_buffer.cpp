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
  Unbind();
  GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
