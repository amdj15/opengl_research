#include "application.h"
#include "../utils/logger.h"

Application::Application(std::string title): m_Window(title), m_Scene(nullptr), m_Input(nullptr) {
  Eng::Utils::Logger::Init();
}

Application::~Application() {
  delete m_Renderer;
  delete m_Scene;
}

void Application::Init(void(*inintScene)(Eng::Scene*)) {
  Graphic::RenderingAPI api = Graphic::RenderingAPI::OpenGL;

  m_Window.Init(api);
  Graphic::CreateContext(api);
  m_Renderer = Graphic::Renderer::Create(api);
  m_Scene = new Eng::Scene();
  m_Input = Eng::Input(m_Window.getGlfwWindow());

  inintScene(m_Scene);

  m_Scene->SetProjection(m_Window.getWidth(), m_Window.getHeight());
}

void Application::Run() {
  float time = glfwGetTime();
  float lastUpdatedTime = time;

  float lastTime = 0.0f;
  float deltaTime = 0.0f;
  int framesCnt = 0;
  int updatesCnt = 0;

  while(m_Window.isOpen()) {
    float currentTime = glfwGetTime();
    float updateTick = 1.0f / 60.0f;

    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (currentTime - lastUpdatedTime > updateTick) {
      update(deltaTime);
      updatesCnt++;
      lastUpdatedTime = glfwGetTime();
    }

    render();
    framesCnt++;

    if (currentTime - time > 1.0f) {
      LOG_INFO("frames: {}, updates: {}", framesCnt, updatesCnt);

      framesCnt = 0;
      updatesCnt = 0;
      time = currentTime;
    }
  }
}

void Application::render() {
  m_Renderer->Clear();

  m_Scene->Render(m_Renderer);

  m_Window.swapBuffers();
  m_Window.pollEvents();
}

void Application::update(float deltaTime) {
  m_Input.Process(deltaTime);
  m_Scene->Update(&m_Input);
}
