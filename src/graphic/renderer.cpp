#include "renderer.h"
#include "../devices/opengl/renderer.h"

using namespace Graphic;

Graphic::Renderer* Renderer::Create(RenderingAPI api) {
  Graphic::Renderer *renderer = nullptr;

  if (api == RenderingAPI::OpenGL) {
    renderer = new Devices::OpenGL::Renderer();
  } else {
    throw std::runtime_error(std::string("Renderer for this api is not supported"));
  }

  return renderer;
}

