#pragma once

#include <GL/glew.h>
#include <csignal>

void GLCleanError();
bool GLLogError(const char* func, const char* file, int line);

#define ASSERT(x) if ((x)) std::raise(SIGINT)

#define GLCall(func) \
  GLCleanError(); \
  func;\
  ASSERT(GLLogError(#func, __FILE__, __LINE__))
