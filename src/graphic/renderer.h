#pragma once

#include "../vertex_array.h"
#include "../index_buffer.h"
#include "../shader_program.h"
#include "api/rendering_context.h"

namespace Graphic {
  class Renderer {
    protected:
      unsigned int m_VaoId;
      unsigned int m_IboId;
      unsigned int m_ShaderId;

    public:
      virtual ~Renderer() = default;

      virtual void clear() const = 0;
      virtual void draw(const VertexArray *vao, const IndexBuffer *ibo, const ShaderProgram &sh) = 0;

      static Renderer* Create(RenderingAPI api);
  };
}