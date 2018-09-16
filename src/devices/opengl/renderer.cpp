#include "renderer.h"
#include "common.h"

using namespace Devices;
using namespace OpenGL;

Renderer::Renderer(){}
Renderer::~Renderer(){}

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
