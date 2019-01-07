#pragma once

#include <glm/glm.hpp>
#include "events/types/move_camera_event.h"
#include <map>

namespace Eng {
  class Camera {
    private:
      glm::vec3 m_Position;
      glm::vec3 m_ViewDirection;
      glm::vec3 m_Up;
      float m_Yaw;
      float m_Pitch;

      std::map<std::string, std::function<void(float)>> m_MovementFnPtrs;

    public:
      Camera();
      ~Camera();
      glm::mat4 ViewMatrix() const;

      inline glm::vec3 GetPosition() const { return m_Position; }

      void OnCameraMouseMove(SharedEvent event);
      void OnCameraKeyboardMove(SharedEvent event);

    private:
      void updateCameraVectors();

      void forward(float offset);
      void backward(float offset);
      void left(float offset);
      void right(float offset);
      void processMouseMovement(float xOffset, float yOffset, float mouseSensitivity);
  };
}
