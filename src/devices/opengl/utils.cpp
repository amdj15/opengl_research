#include "common.h"
#include <iostream>

void GLCleanError() {
  while(glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* func, const char* file, int line) {
  while(GLenum error = glGetError()) {
    std::cout << "[OpenGL ERROR]: CODE " << error << " in " << func << " " << file << ":" << line << std::endl;

    return true;
  }

  return false;
}

