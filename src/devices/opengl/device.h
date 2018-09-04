#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Devices {
  namespace OpenGL {
    class Device {
      public:
        static GLFWwindow* Init(int width, int height, std::string title);
    };
  }
}
