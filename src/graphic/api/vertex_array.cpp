#include "vertex_array.h"
#include "rendering_context.h"
#include <string>

#include "../../devices/opengl/vertex_array.h"

using namespace Graphic;

VertexArray* VertexArray::Create() {
  Context context = CurrentContext();
  VertexArray *vertex_array = nullptr;

  if (context.m_CurrentAPI == Graphic::RenderingAPI::OpenGL) {
    vertex_array = new Devices::OpenGL::VertexArray();
  } else {
    throw std::runtime_error(std::string("Vertex Array for this api is not supported"));
  }

  return vertex_array;
}
