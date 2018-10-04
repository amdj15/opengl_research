#include "common.h"
#include "vertex_array.h"

using namespace Devices;
using namespace OpenGL;

VertexArray::VertexArray() {
  GLCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray() {
  GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::Bind() const {
  GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind() const {
  GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const Graphic::VertexBuffer& vbo, const VertexBufferLayout& layout) {
 vbo.Bind();
 this->Bind();

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
