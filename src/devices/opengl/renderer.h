#pragma once

#include "../../graphic/renderer.h"

namespace Devices {
  namespace OpenGL {
    class Renderer : public Graphic::Renderer {
      public:
        Renderer();
        ~Renderer();

        void Clear() const override;
        void DrawMesh(const Mesh *mesh, Graphic::Shader *sh) override;

      private:
        void bindElements(const Graphic::VertexArray *vao, const Graphic::IndexBuffer *ibo, Graphic::Shader *sh);
        void setTextures(const Mesh *mesh, Graphic::Shader *sh);
    };
  }
}
