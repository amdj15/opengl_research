#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "../graphic/api/rendering_context.h"

class Window {
  private:
    GLFWwindow* m_Window;
    unsigned int m_Width;
    unsigned int m_Height;
    std::string m_Title;
    bool m_InitSuccess;
    std::string m_InitErrorString;
    GLFWmonitor* m_Monitor;

  public:
    Window(unsigned int width, unsigned int height, std::string title);
    Window(std::string title);
    ~Window();

    bool isOpen();
    void swapBuffers();
    void pollEvents();
    void Init(Graphic::RenderingAPI api);

    inline const float getWidth() const {
      return (float)m_Width;
    }

    inline const float getHeight() const {
      return (float)m_Height;
    }

    inline GLFWwindow* getGlfwWindow() const {
      return m_Window;
    }

    inline bool isInitialized() const { return m_InitSuccess; }
};
