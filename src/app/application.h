#pragma once

#include "window.h"
#include <string>

#include "../graphic/renderer.h"
#include "../scene.h"

class Application {
  private:
    Window m_Window;
    Graphic::Renderer *m_Renderer;
    void(*onRender)();
    Eng::Scene m_Scene;

  public:
    Application(std::string title);
    ~Application();
    void Init(void(*inintScene)(Eng::Scene*));
    void Run();

    inline const Window GetWindow() const { return m_Window; }
    inline Graphic::Renderer* GetRenderer() const { return m_Renderer; }
    inline void OnRenderCb(void(*callback)()) { onRender = callback; }

    private:
      void render();
};
