#pragma once

#include <csignal>
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader_program.h"

#define ASSERT(x) if ((x)) std::raise(SIGINT)

#define GLCall(func) \
  GLCleanError(); \
  func;\
  ASSERT(GLLogError(#func, __FILE__, __LINE__))


void GLCleanError();

bool GLLogError(const char* func, const char* file, int line);

class Renderer {
  public:
    void clear() const;
    void draw(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &sh) const;
};
