#pragma once

#include "../../graphic/renderer.h"

namespace Devices {
  namespace OpenGL {
    class Renderer : public Graphic::Renderer {
      public:
        Renderer();
        ~Renderer();

        void Clear() const override;
        void Draw(const Graphic::VertexArray *vao, const Graphic::IndexBuffer *ibo, const Graphic::Shader *sh) override;
    };
  }
}
