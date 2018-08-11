#include <gl/glew.h>
#include "index_buffer.h"
#include "renderer.h"
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count): m_Count(count) {
  GLCall(glGenBuffers(1, &m_RendererId));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(){
  GLCall(glGenBuffers(1, &m_RendererId));
}

IndexBuffer::~IndexBuffer() {
  GLCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count) {
  this->bind();
  m_Count = count;

  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

