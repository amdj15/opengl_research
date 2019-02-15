#include "common.h"
#include "texture_2d.h"
#include <stb_image/stb_image.h>

using namespace Devices;
using namespace OpenGL;

Texture2D::Texture2D(const std::string &pathToFile): Graphic::Texture(), m_BPP(0), m_Buffer(nullptr) {
  stbi_set_flip_vertically_on_load(true);
  m_Buffer = stbi_load(pathToFile.c_str(), &m_Width, &m_Height, &m_BPP, 4);

  if (!m_Buffer) {
    throw std::runtime_error("Texture failed to load at path: " + pathToFile);
  }

  GLCall(glGenTextures(1, &m_RendererId));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer));

  stbi_image_free(m_Buffer);
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture2D::~Texture2D() {
  GLCall(glDeleteTextures(1, &m_RendererId));
}

void Texture2D::Bind(unsigned int slot) const {
  GLCall(glActiveTexture(GL_TEXTURE0 + slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture2D::Unbind() const {
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
