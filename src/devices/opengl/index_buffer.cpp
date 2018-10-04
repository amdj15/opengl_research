#include "common.h"
#include "index_buffer.h"

using namespace Devices;
using namespace OpenGL;

IndexBuffer::IndexBuffer() {
  GLCall(glGenBuffers(1, &m_RendererId));
}

IndexBuffer::~IndexBuffer() {
  GLCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count) {
  Bind();
  m_Count = count;

  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}


