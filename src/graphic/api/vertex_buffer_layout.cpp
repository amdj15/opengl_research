#include "vertex_buffer_layout.h"
#include "rendering_context.h"
#include "../../devices/opengl/common.h"

VertexBufferLayout::VertexBufferLayout(): m_Stride(0){}
VertexBufferLayout::~VertexBufferLayout(){}

void VertexBufferLayout::Push(unsigned int count) {
  Graphic::Context context = Graphic::CurrentContext();

  switch(context.m_CurrentAPI) {
    case Graphic::RenderingAPI::OpenGL:
      m_Elements.push_back({ GL_FLOAT, count });
      break;
    default:
      std::runtime_error("Context not implemented");
  }

  m_Stride += sizeof(count) * count;
}
