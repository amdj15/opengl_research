#include "vertex_buffer.h"
#include "rendering_context.h"
#include "../../devices/opengl/vertex_buffer.h"

using namespace Graphic;

VertexBuffer* VertexBuffer::Create(const void* data, unsigned int size) {
  Context context = CurrentContext();

  switch(context.m_CurrentAPI) {
    case RenderingAPI::OpenGL:
      return new Devices::OpenGL::VertexBuffer(data, size);
  }

  return nullptr;
}

