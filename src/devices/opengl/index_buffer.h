#pragma once

#include "../../graphic/api/index_buffer.h"

namespace Devices {
  namespace OpenGL {
    class IndexBuffer : public Graphic::IndexBuffer {
      public:
        IndexBuffer();
        ~IndexBuffer();

        void SetData(const unsigned int* data, unsigned int count) override;
        void Bind() const override;
        void Unbind() const override;
    };
  }
}
