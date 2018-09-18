#include "application.h"

Application::Application(std::string title): m_Window(title) {}

Application::~Application() {
  delete m_Renderer;
}

void Application::Init() {
  Graphic::RenderingAPI api = Graphic::RenderingAPI::OpenGL;

  m_Window.Init(api);
  Graphic::CreateContext(api);
  m_Renderer = Graphic::Renderer::Create(api);
}

void Application::Run() {}
