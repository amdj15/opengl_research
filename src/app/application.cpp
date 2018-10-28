#include "application.h"

Application::Application(std::string title): m_Window(640, 480, title), m_Input(nullptr) {}

Application::~Application() {
  delete m_Renderer;
}

void Application::Init(void(*inintScene)(Eng::Scene*)) {
  Graphic::RenderingAPI api = Graphic::RenderingAPI::OpenGL;

  m_Window.Init(api);
  Graphic::CreateContext(api);
  m_Renderer = Graphic::Renderer::Create(api);
  m_Scene = Eng::Scene();
  m_Input = Eng::Input(m_Window.getGlfwWindow());

  inintScene(&m_Scene);

  m_Scene.SetProjection(m_Window.getWidth(), m_Window.getHeight());
}

void Application::Run() {
  float lastTime = 0.0f;
  float deltaTime = 0.0f;

  while(m_Window.isOpen()) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    update(deltaTime);
    render();
  }
}

void Application::render() {
  m_Renderer->Clear();

  m_Scene.Render(m_Renderer);

  m_Window.swapBuffers();
  m_Window.pollEvents();
}

void Application::update(float deltaTime) {
  m_Input.Process(deltaTime);
  m_Scene.Update(&m_Input);
}