#include "renderer.h"
#include "common.h"
#include "./shader.h"

using namespace Devices;
using namespace OpenGL;

Renderer::Renderer(){}
Renderer::~Renderer(){}

void Renderer::DrawMesh(const Mesh *mesh, Graphic::Shader *sh) {
  bindElements(mesh->GetVao(), mesh->GetIbo(), sh);
  setTextures(mesh, sh);

  GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIbo()->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
  GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::bindElements(const Graphic::VertexArray *vao, const Graphic::IndexBuffer *ibo, Graphic::Shader *sh) {
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
}

void Renderer::setTextures(const Mesh *mesh, Graphic::Shader *sh) {
  std::map<std::string, Graphic::Texture*> textures = mesh->GetTextures();
  auto shader = static_cast<Shader*>(sh);

  if (textures.count("texture_diffuse") == 1) {
    textures["texture_diffuse"]->Bind(0);
    shader->SetUniform1i("texture_diffuse", 0);
  }

  if (textures.count("texture_specular") == 1) {
    textures["texture_specular"]->Bind(1);
    shader->SetUniform1i("texture_specular", 1);
  }

  if (textures.count("texture_normal") == 1) {
    textures["texture_normal"]->Bind(2);
    shader->SetUniform1i("texture_normal", 2);
  }

  shader->SetUniform1f("material.shininess", mesh->m_Materials.shininess);
  shader->SetUniform1f("material.specularStrength", mesh->m_Materials.shininessStrength);
}
