#include <glm/glm.hpp>

class Camera {
  private:
    glm::vec3 m_Position;
    glm::vec3 m_ViewDirection;
    glm::vec3 m_Up;
    float m_Yaw;
    float m_Pitch;
    float m_MouseSensitivity;

  public:
    Camera();
    ~Camera();
    glm::mat4 getViewMatrix() const;

    void forward(float offset);
    void backward(float offset);
    void left(float offset);
    void right(float offset);

    void processMouseMovement(float xOffset, float yOffset);

  private:
    void updateCameraVectors();
};
