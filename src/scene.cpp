#include "scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Eng;

void Scene::AddGameObject(ShGameObject gameObject) {
  gameObject->Init();
  m_GameObjects.push_back(gameObject);
}

void Scene::Render(Graphic::Renderer *renderer) {
  for(ShGameObject gameObject : m_GameObjects) {
    Model *model = gameObject->GetModel();
    Graphic::Shader *shader = gameObject->GetShader();

    for(Mesh *mesh : model->getMeshes()) {
      renderer->Draw(mesh->GetVao(), mesh->GetIbo(), shader);
    }
  }
}

void Scene::Update(const Input* input) {
  m_Camera.Update(input);

  std::map<Graphic::Shader*, std::vector<ShGameObject>> gameObjectsShadersMap;
  for(ShGameObject gameObject : m_GameObjects) {
    gameObjectsShadersMap[gameObject->GetShader()].push_back(gameObject);
  }

  for(auto const &item : gameObjectsShadersMap) {
    Graphic::Shader *shader = item.first;
    glm::mat4 view = m_Camera.ViewMatrix();

    shader->Bind();
    shader->SetUniformMatrix4fv("u_Projection", glm::value_ptr(m_Projection));
    shader->SetUniformMatrix4fv("u_View", glm::value_ptr(view));

    for(ShGameObject gameObject : item.second) {
      glm::mat4 modelMatrix = gameObject->GetModelMatrix();
      shader->SetUniformMatrix4fv("u_Model", glm::value_ptr(modelMatrix));
    }
  }
}

void Scene::SetProjection(float width, float height) {
  m_Projection = glm::perspective(glm::radians(45.0f), width / height, 1.0f, 1000.0f);
}