#include <glm/glm.hpp>

class Camera {
  private:
    glm::vec3 m_Position;
    glm::vec3 m_ViewDirection;
    glm::vec3 m_Up;

  public:
    Camera();
    ~Camera();
    glm::mat4 getViewMatrix() const;
};
