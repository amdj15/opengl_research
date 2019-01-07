#pragma once

#include "app/window.h"
#include <map>

namespace Eng {
  class Input {
    private:
      GLFWwindow *m_Window;
      float m_DeltaTime;
      double m_XCoursor;
      double m_YCoursor;
      double m_XCoursorOffset;
      double m_YCoursorOffset;
      bool m_IsFirstMouse;
      float m_MouseSensitivity;
      float m_MoveSensitivity;
      float m_OriginMoveSensitivity;
      std::map<int, int> m_Keys;
      std::map<int, std::string> m_MoveDirectionsKeys;

    public:
      Input(GLFWwindow *window);
      ~Input();

      void Process(float deltaTime);

      inline const float DeltaTime() const { return m_DeltaTime; }
      inline const double GetXOffset() const { return m_XCoursorOffset; }
      inline const double GetYOffset() const { return m_YCoursorOffset; }
      inline const float GetMoveSensitivity() const { return m_MoveSensitivity; }
      inline const float GetMouseSensitivity() const { return m_MouseSensitivity; }

    private:
      void processMouse();
      void processKeyboard();
      void dispatchEvents();
  };
}
