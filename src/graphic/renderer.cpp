#include "../devices/opengl/renderer.h"

using namespace Graphic;

Graphic::Renderer* Renderer::Create(RenderingAPI api) {
  Graphic::Renderer *renderer = nullptr;

  switch(api) {
    case RenderingAPI::OpenGL:
        renderer = new Devices::OpenGL::Renderer();
      break;
    default:
      throw std::runtime_error("Renderer for this api is not supported");
  }

  return renderer;
}

