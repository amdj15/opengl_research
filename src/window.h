#include <GLFW/glfw3.h>
#include <string>

class Window {
  private:
    GLFWwindow* m_Window;
    unsigned int m_Width;
    unsigned int m_Height;
    std::string m_Title;
    bool m_InitSuccess;
    std::string m_InitErrorString;

  public:
    Window(unsigned int width, unsigned int height, std::string title);
    ~Window();

    bool isOpen();
    void swapBuffers();
    void pollEvents();

    inline const float getWidth() const {
      return (float)m_Width;
    }

    inline const float getHeight() const {
      return (float)m_Height;
    }
};
