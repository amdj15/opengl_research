#include <iostream>
#include <GL/glew.h>

#include "window.h"

Window::Window(std::string title) {
  m_Title = title;

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

  this->init();
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

  this->init();
}

Window::~Window() {
  glfwTerminate();
}

void Window::init() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Monitor, NULL);
  if (!m_Window) {
    glfwTerminate();

    m_InitErrorString = "Can't create window";
    return;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1);
  glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (glewInit() != GLEW_OK) {
    m_InitErrorString = "Can't init glew";
    return;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

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
