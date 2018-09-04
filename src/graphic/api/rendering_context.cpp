#include <string>

#include "rendering_context.h"
#include "../../devices/opengl/context.h"

void Graphic::Context::Create(RenderingAPI api) {
  if (api == RenderingAPI::OpenGL) {
    m_Context = Devices::GLContext();
  } else {
    throw std::runtime_error(std::string("Rendering API is not supported"));
  }
}
