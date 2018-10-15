#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"

using namespace Eng;

Camera::Camera(): m_Position(0.0f, 0.0f, 3.0f),
                  m_ViewDirection(0.0f, 0.0f, -1.0f),
                  m_Up(0.0f, 1.0f, 0.0f),
                  m_Yaw(-90.0f),
                  m_Pitch(0.0f),
                  m_MouseSensitivity(0.05f),
                  m_MoveSensitivity(5.0f) {}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(m_Position, m_Position + m_ViewDirection, m_Up);
}

void Camera::Update(const Input* input) {
  std::map<InputMoveDirection, InputMoveDirection> directions = input->GetMoveDirection();
  float offset = input->DeltaTime() * m_MoveSensitivity;

  if (directions.count(InputMoveDirection::BACKWARD) > 0) {
    backward(offset);
  }

  if (directions.count(InputMoveDirection::FORWARD) > 0) {
    forward(offset);
  }

  if (directions.count(InputMoveDirection::LEFT) > 0) {
    left(offset);
  }

  if (directions.count(InputMoveDirection::RIGHT) > 0) {
    right(offset);
  }
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

void Camera::processMouseMovement(float xOffset, float yOffset) {
  xOffset *= m_MouseSensitivity;
  yOffset *= m_MouseSensitivity;

  m_Yaw += xOffset;
  m_Pitch += yOffset;

  if (m_Pitch > 89.0f)
      m_Pitch = 89.0f;
  if (m_Pitch < -89.0f)
      m_Pitch = -89.0f;

  updateCameraVectors();
}