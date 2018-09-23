#pragma once

#include "window.h"
#include <string>

#include "../graphic/renderer.h"

class Application {
  private:
    Window m_Window;
    Graphic::Renderer *m_Renderer;

  public:
    Application(std::string title);
    ~Application();
    void Init();
    void Run();

    inline const Window GetWindow() const { return m_Window; }
    inline Graphic::Renderer* GetRenderer() const { return m_Renderer; }
};
