#pragma once

namespace Graphic {
  class VertexBuffer {
    protected:
      unsigned int m_RendererId;

    public:
      virtual ~VertexBuffer() = default;

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;

      static VertexBuffer* Create(const void* data, unsigned int size);

      inline unsigned int GetRendererId() const {
        return m_RendererId;
      }
  };
}
