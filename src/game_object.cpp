#include "game_object.h"
#include "utils/logger.h"
#include "ecs/components/position_component.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Eng;

GameObject::GameObject(const std::string &pathToFile) {
  m_Model = new Model(pathToFile);
  m_Shader = Graphic::Shader::CreateFromFile("./shaders/model.glsl");
  m_Matrix = glm::mat4(1.0f);
}

GameObject::GameObject(const std::string &pathToFile, const std::string &shaderFilePath) {
  m_Model = new Model(pathToFile);
  m_Shader = Graphic::Shader::CreateFromFile(shaderFilePath);
}

GameObject::~GameObject() {
  delete m_Model;
  delete m_Shader;

  LOG_DEBUG("game object was deleted");
}

void GameObject::Init() {
  m_Model->Load();
  m_Shader->Init();
}

glm::mat4 GameObject::GetModelMatrix() {
  auto components = m_Entity->GetComponents();
  auto component = static_cast<ECS::PositionComponent*>(components[m_Entity->getComponentTypeId<ECS::PositionComponent>()]);

  if (component->m_X == 0 && component->m_Y == 0 && component->m_Z == 0) {
    return m_Matrix;
  }

  m_Matrix = glm::translate(m_Matrix, glm::vec3(component->m_X, component->m_Y, component->m_Z));

  component->m_X = 0;
  component->m_Y = 0;
  component->m_Z = 0;

  return m_Matrix;
}
