#include <stdexcept>
#include "common.h"
#include "context.h"
#include "../../utils/logger.h"

using namespace Devices;

GLContext::GLContext() {
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Cannot initialize glew for OpenGL");
  }

  LOG_DEBUG("OpenGL version: {0}", glGetString(GL_VERSION));
  LOG_DEBUG("GLSL version: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
  LOG_DEBUG("Vendor: {0}", glGetString(GL_VENDOR));
  LOG_DEBUG("Renderer: {0}", glGetString(GL_RENDERER));

  GLCall(glEnable(GL_CULL_FACE));
  GLCall(glCullFace(GL_BACK));
  GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_DEPTH_TEST));
}

GLContext::~GLContext() {}
