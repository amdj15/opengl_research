#include "renderer.h"
#include "common.h"

using namespace Devices;
using namespace OpenGL;

Renderer::Renderer(){}
Renderer::~Renderer(){}

void Renderer::Draw(const Graphic::VertexArray *vao, const Graphic::IndexBuffer *ibo, const Graphic::Shader *sh) {
  if (vao->GetRendererId() != m_VaoId) {
    vao->Bind();
    m_VaoId = vao->GetRendererId();
  }

  if (ibo->getRendererId() != m_IboId) {
    ibo->Bind();
    m_IboId = ibo->getRendererId();
  }

  if (sh->GetId() != m_ShaderId) {
    sh->Bind();
    m_ShaderId = sh->GetId();
  }

  GLCall(glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
