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
      double m_XCoursor;
      double m_YCoursor;
      double m_XCoursorOffset;
      double m_YCoursorOffset;
      bool m_IsFirstMouse;

    public:
      Input(GLFWwindow *window);
      ~Input();

      void Process(float deltaTime);
      std::map<InputMoveDirection, InputMoveDirection> GetMoveDirection() const;

      inline const float DeltaTime() const { return m_DeltaTime; }
      inline const double GetXOffset() const { return m_XCoursorOffset; }
      inline const double GetYOffset() const { return m_YCoursorOffset; }

    private:
      void updateCoursor();
  };
}
