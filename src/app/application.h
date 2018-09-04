#pragma once

#include "window.h"
#include <string>

class Application {
  private:
    bool m_IsRanning;
    Window m_Window;

  public:
    Application(std::string title);
    ~Application();
    void Init();
    void Run();

    inline const Window GetWindow() const { return m_Window; }
};
