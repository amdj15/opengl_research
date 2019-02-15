#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "events/dispatcher.h"

using namespace Eng;

Camera::Camera(): m_Position(0.0f, 0.0f, 3.0f),
                  m_ViewDirection(0.0f, 0.0f, -1.0f),
                  m_Up(0.0f, 1.0f, 0.0f),
                  m_Yaw(-90.0f),
                  m_Pitch(0.0f)
{
  m_MovementFnPtrs["forward"] = std::bind(&Camera::forward, this, std::placeholders::_1);
  m_MovementFnPtrs["backward"] = std::bind(&Camera::backward, this, std::placeholders::_1);
  m_MovementFnPtrs["left"] = std::bind(&Camera::left, this, std::placeholders::_1);
  m_MovementFnPtrs["right"] = std::bind(&Camera::right, this, std::placeholders::_1);

  Events::Dispatcher::AddEventListener("moveCameraMouse", std::bind(&Camera::OnCameraMouseMove, this, std::placeholders::_1));
  Events::Dispatcher::AddEventListener("moveCameraKeyboard", std::bind(&Camera::OnCameraKeyboardMove, this, std::placeholders::_1));
}

Camera::~Camera() {
  Events::Dispatcher::RemoveEventListener("moveCameraMouse", std::bind(&Camera::OnCameraMouseMove, this, std::placeholders::_1));
  Events::Dispatcher::RemoveEventListener("moveCameraKeyboard", std::bind(&Camera::OnCameraKeyboardMove, this, std::placeholders::_1));
}

glm::mat4 Camera::ViewMatrix() const {
  return glm::lookAt(m_Position, m_Position + m_ViewDirection, m_Up);
}

void Camera::OnCameraMouseMove(SharedEvent e) {
  auto event = std::static_pointer_cast<Eng::Events::MoveCameraEvent>(e);
  processMouseMovement(event->xOffset, event->yOffset, event->sensetivity);
  updateCameraVectors();
}

void Camera::OnCameraKeyboardMove(SharedEvent e) {
  auto event = std::static_pointer_cast<Eng::Events::MoveCameraEvent>(e);
  m_MovementFnPtrs[event->direction](event->deltaTime * event->sensetivity);
}

void Camera::updateCameraVectors() {
  glm::vec3 direction;

  direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  direction.y = sin(glm::radians(m_Pitch));
  direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

  m_ViewDirection = glm::normalize(direction);
}

void Camera::forward(float offset) {
  m_Position += offset * m_ViewDirection;
}

void Camera::backward(float offset) {
  m_Position -= offset * m_ViewDirection;
}

void Camera::left(float offset) {
  m_Position -= glm::normalize(glm::cross(m_ViewDirection, m_Up)) * offset;
}

void Camera::right(float offset) {
  m_Position += glm::normalize(glm::cross(m_ViewDirection, m_Up)) * offset;
}

void Camera::processMouseMovement(float xOffset, float yOffset, float mouseSensitivity) {
  xOffset *= mouseSensitivity;
  yOffset *= mouseSensitivity;

  m_Yaw += xOffset;
  m_Pitch += yOffset;

  if (m_Pitch > 89.0f) {
    m_Pitch = 89.0f;
  }

  if (m_Pitch < -89.0f) {
    m_Pitch = -89.0f;
  }
}
