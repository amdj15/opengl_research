#include "input.h"
#include <iostream>

using namespace Eng;

Input::Input(GLFWwindow *window): m_Window(window) {}

Input::~Input() {}

void Input::Process(float deltaTime) {
  m_DeltaTime = deltaTime;
  m_Keys.clear();

  for(int key = GLFW_KEY_A; key <= GLFW_KEY_Z; key++) {
    if (glfwGetKey(m_Window, key) == GLFW_PRESS) {
      m_Keys[key] = key;
    }
  }
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
