#pragma once

#include "api/vertex_array.h"
#include "api/index_buffer.h"
#include "shader.h"
#include "api/rendering_context.h"
#include "../mesh.h"

namespace Graphic {
  class Renderer {
    protected:
      unsigned int m_VaoId;
      unsigned int m_IboId;
      unsigned int m_ShaderId;

    public:
      virtual ~Renderer() = default;
      virtual void Clear() const = 0;

      virtual void DrawMesh(const Mesh *mesh, Shader *sh) = 0;

      static Renderer* Create(RenderingAPI api);
  };
}
