#pragma once

#include <GL/glew.h>

#define ASSERT(x) if ((x)) std::raise(SIGINT)

#define GLCall(func) \
  GLCleanError(); \
  func;\
  ASSERT(GLLogError(#func, __FILE__, __LINE__))
