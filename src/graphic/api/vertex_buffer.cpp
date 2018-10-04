#include "rendering_context.h"
#include "../../devices/opengl/vertex_buffer.h"
#include <stdexcept>

using namespace Graphic;

VertexBuffer* VertexBuffer::Create(const void* data, unsigned int size) {
  Context context = CurrentContext();
  VertexBuffer* buffer = nullptr;

  switch(context.m_CurrentAPI) {
    case RenderingAPI::OpenGL:
      buffer = new Devices::OpenGL::VertexBuffer(data, size);
      break;
    default:
      std::runtime_error("Can't generate vertex buffer for current api");
  }

  return buffer;
}

