#include "common.h"
#include "../../utils/logger.h"

void GLCleanError() {
  while(glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* func, const char* file, int line) {
  while(GLenum error = glGetError()) {
    LOG_ERROR("[OpenGL ERROR]: CODE {0} in {1} {2}:{3}", error, func, file, line);
    return true;
  }

  return false;
}

