#include "input.h"
#include <iostream>

using namespace Eng;

Input::Input(GLFWwindow *window): m_Window(window), m_IsFirstMouse(true) {}

Input::~Input() {}

void Input::Process(float deltaTime) {
  m_DeltaTime = deltaTime;
  m_Keys.clear();

  for(int key = GLFW_KEY_A; key <= GLFW_KEY_Z; key++) {
    if (glfwGetKey(m_Window, key) == GLFW_PRESS) {
      m_Keys[key] = key;
    }
  }

  updateCoursor();
}

std::map<InputMoveDirection, InputMoveDirection> Input::GetMoveDirection() const {
  std::map<InputMoveDirection, InputMoveDirection> directions;

  if (m_Keys.count(GLFW_KEY_W) > 0) {
    directions[InputMoveDirection::FORWARD] = InputMoveDirection::FORWARD;
  }

  if (m_Keys.count(GLFW_KEY_S) > 0) {
    directions[InputMoveDirection::BACKWARD] = InputMoveDirection::BACKWARD;
  }

  if (m_Keys.count(GLFW_KEY_A) > 0) {
    directions[InputMoveDirection::LEFT] = InputMoveDirection::LEFT;
  }

  if (m_Keys.count(GLFW_KEY_D) > 0) {
    directions[InputMoveDirection::RIGHT] = InputMoveDirection::RIGHT;
  }

  return directions;
}

void Input::updateCoursor() {
  double xpos, ypos;
  glfwGetCursorPos(m_Window, &xpos, &ypos);

  if (m_IsFirstMouse) {
    m_IsFirstMouse = false;
    m_XCoursor = xpos;
    m_YCoursor = ypos;
  }

  m_XCoursorOffset = xpos - m_XCoursor;
  m_YCoursorOffset = ypos - m_YCoursor;

  m_XCoursor = xpos;
  m_YCoursor = ypos;
}
