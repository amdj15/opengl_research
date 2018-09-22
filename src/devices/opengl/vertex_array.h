#pragma once

#include "../../graphic/api/vertex_buffer.h"
#include "../../vertex_buffer_layout.h"
#include "../../graphic/api/vertex_array.h"

namespace Devices {
  namespace OpenGL {
    class VertexArray : public Graphic::VertexArray {
      public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const Graphic::VertexBuffer& vbo, const VertexBufferLayout& layout) override;
        void Bind() const override;
        void Unbind() const override;
    };
  }
}
