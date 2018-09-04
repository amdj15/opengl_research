#include "application.h"

Application::Application(std::string title): m_Window(title) {}

Application::~Application() {}

void Application::Init() {
  m_Window.Init(Graphic::RenderingAPI::OpenGL);
  Graphic::Context::Create(Graphic::RenderingAPI::OpenGL);
}

void Application::Run() {}
