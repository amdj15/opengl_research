#pragma once

#include "app/window.h"
#include <map>

namespace Eng {
  enum class InputMoveDirection { LEFT, RIGHT, FORWARD, BACKWARD, NONE };

  class Input {
    private:
      GLFWwindow *m_Window;
      std::map<int, int> m_Keys;
      float m_DeltaTime;

    public:
      Input(GLFWwindow *window);
      ~Input();

      void Process(float deltaTime);
      std::map<InputMoveDirection, InputMoveDirection> GetMoveDirection() const;

      inline const float DeltaTime() const { return m_DeltaTime; }
  };
}
