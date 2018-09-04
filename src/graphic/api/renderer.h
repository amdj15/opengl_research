#pragma once

#include <csignal>
#include "../../vertex_array.h"
#include "../../index_buffer.h"
#include "../../shader_program.h"

void GLCleanError();

bool GLLogError(const char* func, const char* file, int line);

class Renderer {
  private:
    unsigned int m_VaoId;
    unsigned int m_IboId;
    unsigned int m_ShaderId;

  public:
    Renderer();
    void clear() const;
    void draw(const VertexArray *vao, const IndexBuffer *ibo, const ShaderProgram &sh);
};
