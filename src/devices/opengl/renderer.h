#pragma once

#include "../../graphic/renderer.h"

namespace Devices {
  namespace OpenGL {
    class Renderer : public Graphic::Renderer {
      public:
        Renderer();
        ~Renderer();

        void clear() const override;
        void draw(const Graphic::VertexArray *vao, const IndexBuffer *ibo, const ShaderProgram &sh) override;
    };
  }
}
