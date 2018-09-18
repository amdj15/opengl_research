#pragma once

#include "../../graphic/api/vertex_buffer.h"

namespace Devices {
  namespace OpenGL {
    class VertexBuffer : public Graphic::VertexBuffer {
      public:
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void bind() const override;
        void unbind() const override;
    };
  }
}
