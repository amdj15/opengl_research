#include "scene.h"

using namespace Eng;

Scene::Scene() {
  m_Camera = Camera();
}

Scene::~Scene() {}

void Scene::AddGameObject(GameObject *gameObject) {
  gameObject->Init();
  m_GameObjects.push_back(gameObject);
}

void Scene::Render(Graphic::Renderer *renderer) {
  for(GameObject *gameObject : m_GameObjects) {
    Model *model = gameObject->GetModel();
    Graphic::Shader *shader = gameObject->GetShader();

    for(Mesh *mesh : model->getMeshes()) {
      renderer->Draw(mesh->GetVao(), mesh->GetIbo(), shader);
    }
  }
}