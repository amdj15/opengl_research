#include <fstream>
#include <sstream>
#include "shader.h"
#include "api/rendering_context.h"
#include "../devices/opengl/shader.h"

using namespace Graphic;

Shader::Shader(std::string filepath): m_FilePath(filepath) {}

Shader* Shader::CreateFromFile(std::string filepath) {
  Shader* shader = nullptr;
  Context context = CurrentContext();

  switch(context.m_CurrentAPI) {
    case Graphic::RenderingAPI::OpenGL:
      shader = new Devices::OpenGL::Shader(filepath);
      break;
    default:
      throw std::runtime_error("Shaders for current api not impemented");
  }

  return shader;
}

std::string Shader::readFromFile(const std::string &resourcepath) {
  std::ifstream file;
  file.open(resourcepath);

  if (!file.is_open()) {
    throw std::runtime_error(std::string("Failed to open file: ") + resourcepath);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}