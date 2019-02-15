#pragma once

#include "window.h"
#include <string>

#include "../graphic/renderer.h"
#include "../scene.h"
#include "../input.h"

class Application {
  private:
    Window m_Window;
    Graphic::Renderer *m_Renderer;
    Eng::Scene* m_Scene;
    Eng::Input m_Input;

  public:
    Application(std::string title);
    ~Application();
    void Init(void(*inintScene)(Eng::Scene*));
    void Run();

    inline const Window GetWindow() const { return m_Window; }
    inline Graphic::Renderer* GetRenderer() const { return m_Renderer; }

    private:
      void render();
      void update(float deltaTime);
};
