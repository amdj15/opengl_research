#include "scene.h"

using namespace Eng;

Scene::Scene() {
  m_Camera = Camera();
}

Scene::~Scene() {}

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
}