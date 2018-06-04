#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
  private:
    unsigned int m_RendererId;
  public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;

    inline unsigned int getRendererId() const {
      return m_RendererId;
    }
};
