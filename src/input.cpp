#include "input.h"
#include "events/types/arrow_pressed_event.h"
#include "events/types/move_camera_event.h"
#include "events/dispatcher.h"

using namespace Eng;

Input::Input(GLFWwindow *window): m_Window(window), m_IsFirstMouse(true),
                                  m_MouseSensitivity(0.05f),
                                  m_OriginMoveSensitivity(5.0f)
{
  m_MoveSensitivity = m_OriginMoveSensitivity;

  m_MoveDirectionsKeys[GLFW_KEY_A] = "left";
  m_MoveDirectionsKeys[GLFW_KEY_D] = "right";
  m_MoveDirectionsKeys[GLFW_KEY_S] = "backward";
  m_MoveDirectionsKeys[GLFW_KEY_W] = "forward";
}

Input::~Input() {}

void Input::Process(float deltaTime) {
  m_DeltaTime = deltaTime;

  processKeyboard();
  processMouse();
  dispatchEvents();
}

void Input::processMouse() {
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

void Input::processKeyboard() {
  m_Keys.clear();

  for(int key = GLFW_KEY_SPACE; key <= GLFW_KEY_Z; key++) {
    if (glfwGetKey(m_Window, key) == GLFW_PRESS) {
      m_Keys[key] = key;
    }
  }

  if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    m_MoveSensitivity = m_OriginMoveSensitivity * 5;
  } else {
    m_MoveSensitivity = m_OriginMoveSensitivity;
  }
}

void Input::dispatchEvents() {
  if (m_XCoursorOffset != 0 || m_YCoursorOffset != 0) {
    auto moveCameraMouseEvent = std::make_shared<Events::MoveCameraEvent>(m_XCoursorOffset, m_YCoursorOffset, m_MouseSensitivity);
    Eng::Events::Dispatcher::Emit("moveCameraMouse", moveCameraMouseEvent);
  }

  for(int key = GLFW_KEY_RIGHT; key <= GLFW_KEY_UP; key++) {
    std::string eventName = "ArrowKeyPressed";

    if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)
      Events::Dispatcher::Emit(eventName, std::make_shared<Events::ArrowPressedEvent>(Events::Arrows::left));

    if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      Events::Dispatcher::Emit(eventName, std::make_shared<Events::ArrowPressedEvent>(Events::Arrows::right));

    if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)
      Events::Dispatcher::Emit(eventName, std::make_shared<Events::ArrowPressedEvent>(Events::Arrows::up));

    if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
      Events::Dispatcher::Emit(eventName, std::make_shared<Events::ArrowPressedEvent>(Events::Arrows::down));
  }

  for(auto const &item : m_MoveDirectionsKeys) {
    if (glfwGetKey(m_Window, item.first) == GLFW_PRESS) {
      auto moveCameraKeyboardEvent = std::make_shared<Events::MoveCameraEvent>(0, 0, m_MoveSensitivity);
      moveCameraKeyboardEvent->direction = item.second;
      moveCameraKeyboardEvent->deltaTime = m_DeltaTime;
      Events::Dispatcher::Emit("moveCameraKeyboard", moveCameraKeyboardEvent);
    }
  }

  if (glfwGetKey(m_Window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
    Events::Dispatcher::Emit("popLastGameObject", std::make_shared<Events::Event>());
  }
}
