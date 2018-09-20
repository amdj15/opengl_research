#include <string>

#include "rendering_context.h"
#include "../../devices/opengl/context.h"

namespace Graphic {
  Context context;

  void CreateContext(RenderingAPI api) {
    if (api == RenderingAPI::OpenGL) {
      context = Devices::GLContext();
    } else {
      throw std::runtime_error(std::string("Rendering API is not supported"));
    }

    context.m_CurrentAPI = api;
  }

  Context CurrentContext() {
    return context;
  }
}
