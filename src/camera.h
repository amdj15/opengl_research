#pragma once

#include <glm/glm.hpp>
#include "input.h"

namespace Eng {
  class Camera {
    private:
      glm::vec3 m_Position;
      glm::vec3 m_ViewDirection;
      glm::vec3 m_Up;
      float m_Yaw;
      float m_Pitch;

    public:
      Camera();
      ~Camera();
      glm::mat4 ViewMatrix() const;

      inline glm::vec3 GetPosition() const { return m_Position; }

      void Update(const Input* input);

    private:
      void updateCameraVectors();

      void forward(float offset);
      void backward(float offset);
      void left(float offset);
      void right(float offset);
      void processMouseMovement(float xOffset, float yOffset, float mouseSensitivity);
  };
}
