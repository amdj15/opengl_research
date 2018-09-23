#include <string>

#include "rendering_context.h"
#include "../../devices/opengl/context.h"

namespace Graphic {
  Context context;

  void CreateContext(RenderingAPI api) {
    switch(api) {
      case RenderingAPI::OpenGL:
        context = Devices::GLContext();
        break;
      default:
        throw std::runtime_error("Rendering API is not supported");
    }

    context.m_CurrentAPI = api;
  }

  Context CurrentContext() {
    return context;
  }
}
