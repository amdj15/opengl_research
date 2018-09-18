#pragma once

#include "rendering_context.h"

namespace Graphic {
  class VertexBuffer {
    protected:
      unsigned int m_RendererId;

    public:
      virtual void bind() const = 0;
      virtual void unbind() const = 0;

      static VertexBuffer* Create(const void* data, unsigned int size);

      inline unsigned int getRendererId() const {
        return m_RendererId;
      }
  };
}
