#include <iostream>
#include "common.h"
#include "context.h"

using namespace Devices;

GLContext::GLContext() {
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Cannot initialize glew for OpenGL");
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

GLContext::~GLContext() {}
