#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

namespace Graphic {
  class VertexArray {
    protected:
      unsigned int m_RendererId;

    public:
      static VertexArray* Create();

      VertexArray() = default;
      virtual ~VertexArray() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;
      virtual void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) = 0;

      inline unsigned int GetRendererId() const { return m_RendererId; }
  };
}
