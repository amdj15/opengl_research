#include "texture.h"
#include "rendering_context.h"
#include "../../devices/opengl/texture_2d.h"

using namespace Graphic;

Texture::Texture(): m_Width(0), m_Height(0) {}

Texture* Texture::Create2DFromFile(const std::string &pathToFile) {
  Texture* texture = nullptr;
  Context context = CurrentContext();

  switch(context.m_CurrentAPI) {
    case RenderingAPI::OpenGL:
      texture = new Devices::OpenGL::Texture2D(pathToFile);
      break;
    default:
      throw std::runtime_error("Texture for current api not impemented");
  }

  return texture;
}