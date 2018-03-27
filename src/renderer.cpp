#include <iostream>
#include <GL/glew.h>

#include "renderer.h"

void GLCleanError() {
  while(glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* func, const char* file, int line) {
  while(GLenum error = glGetError()) {
    std::cout << "[OpenGL ERROR]: CODE " << error << " in " << func << " " << file << ":" << line << std::endl;

    return true;
  }

  return false;
}

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ibo, const ShaderProgram &sh) const {
  vao.bind();
  ibo.bind();

  GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
