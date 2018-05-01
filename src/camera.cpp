#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

Camera::Camera(): m_Position(0.0f, 0.0f, 3.0f),
                  m_ViewDirection(0.0f, 0.0f, -1.0f),
                  m_Up(0.0f, 1.0f, 0.0f) {}

Camera::~Camera() {}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(m_Position, m_Position + m_ViewDirection, m_Up);
}
