#include "vertex_array.h"
#include "rendering_context.h"
#include <string>

#include "../../devices/opengl/vertex_array.h"

using namespace Graphic;

VertexArray* VertexArray::Create() {
  Context context = CurrentContext();
  VertexArray *vertex_array = nullptr;

  switch(context.m_CurrentAPI) {
    case Graphic::RenderingAPI::OpenGL:
      vertex_array = new Devices::OpenGL::VertexArray();
      break;
    default:
      throw std::runtime_error("Vertex Array for this api is not supported");
  }

  return vertex_array;
}
