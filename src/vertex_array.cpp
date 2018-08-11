#include <GL/glew.h>

#include "renderer.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include <iostream>

VertexArray::VertexArray() {
  GLCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray() {
  GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) {
 vbo.bind();
 this->bind();

  auto elements = layout.getElements();
  unsigned int offset = 0;

  for(int i = 0; i < elements.size(); i++) {
    auto elem = elements[i];

    GLCall(glEnableVertexAttribArray(i));
    GLCall(
      glVertexAttribPointer(i, elem.count, elem.type, GL_FALSE, layout.getStride(), (const void*)(size_t)offset)
    );

    offset += elem.count * sizeof(elem.type);
  }
}

void VertexArray::bind() const {
  GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::unbind() const {
  GLCall(glBindVertexArray(0));
}
