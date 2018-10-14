#include "application.h"

Application::Application(std::string title): m_Window(title) {}

Application::~Application() {
  delete m_Renderer;
}

void Application::Init(void(*inintScene)(Eng::Scene*)) {
  Graphic::RenderingAPI api = Graphic::RenderingAPI::OpenGL;

  m_Window.Init(api);
  Graphic::CreateContext(api);
  m_Renderer = Graphic::Renderer::Create(api);
  m_Scene = Eng::Scene();

  inintScene(&m_Scene);
}

void Application::Run() {
  while(m_Window.isOpen()) {
    render();
  }
}

void Application::render() {
  m_Renderer->Clear();

  m_Scene.Render(m_Renderer);

  m_Window.swapBuffers();
  m_Window.pollEvents();
}
