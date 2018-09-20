#include <iostream>
#include "window.h"
#include "../devices/opengl/device.h"

Window::Window(std::string title): m_Title(title) {
  if (!glfwInit()) {
    m_InitErrorString = "Can't initialize GLFW";
    return;
  }

  GLFWmonitor* m_Monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);

  m_Width = mode->width;
  m_Height = mode->height;
  m_InitSuccess = false;
  m_InitErrorString = "";
}

Window::Window(unsigned int width, unsigned int height, std::string title)
  : m_Width(width),
    m_Height(height),
    m_Title(title),
    m_InitSuccess(false),
    m_InitErrorString(""),
    m_Monitor(nullptr)
{
  if (!glfwInit()) {
    m_InitErrorString = "Can't initialize GLFW";
    return;
  }
}

Window::~Window() {
  glfwTerminate();
}

void Window::Init(Graphic::RenderingAPI api) {
  if (api == Graphic::RenderingAPI::OpenGL) {
    m_Window = Devices::OpenGL::Device::Init(m_Width, m_Height, m_Title);
  }

  if (!m_Window) {
    glfwTerminate();

    m_InitErrorString = "Can't create window";
    return;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1);
  glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  m_InitSuccess = true;
 }

bool Window::isOpen() {
 return !glfwWindowShouldClose(m_Window);
}

void Window::swapBuffers() {
  glfwSwapBuffers(m_Window);
}

void Window::pollEvents() {
  glfwPollEvents();
}
