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

Renderer::Renderer() {
  GLCall(glEnable(GL_CULL_FACE));
  GLCall(glCullFace(GL_BACK));
  // GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_DEPTH_TEST));
}

void Renderer::draw(const VertexArray *vao, const IndexBuffer *ibo, const ShaderProgram &sh) {
  if (vao->getRendererId() != m_VaoId) {
    vao->bind();
    m_VaoId = vao->getRendererId();
  }

  if (ibo->getRendererId() != m_IboId) {
    ibo->bind();
    m_IboId = ibo->getRendererId();
  }

  if (sh.getId() != m_ShaderId) {
    sh.bind();
    m_ShaderId = sh.getId();
  }

  GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
