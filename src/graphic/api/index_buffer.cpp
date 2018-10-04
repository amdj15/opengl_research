#include "index_buffer.h"
#include "rendering_context.h"
#include <stdexcept>
#include "../../devices/opengl/index_buffer.h"

using namespace Graphic;

IndexBuffer* IndexBuffer::Create() {
  Context context = CurrentContext();
  IndexBuffer* buffer = nullptr;

  switch(context.m_CurrentAPI) {
    case RenderingAPI::OpenGL:
        buffer = new Devices::OpenGL::IndexBuffer();
      break;
    default:
      throw std::runtime_error("Rendering api is not supported for index buffer");
  }

  return buffer;
}