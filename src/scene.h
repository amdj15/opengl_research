#pragma once

#include "game_object.h"
#include "camera.h"
#include "graphic/renderer.h"
#include "input.h"
#include "ecs/manager.h"
#include "ecs/systems/system.h"

namespace Eng {
  class Scene {
    private:
      Camera m_Camera;
      std::vector<ShGameObject> m_GameObjects;
      glm::mat4 m_Projection;
      Eng::ECS::Manager m_EntitieManager;
      std::vector<Eng::ECS::System*> m_Systems;

    public:
      Scene();
      ~Scene();

      void AddGameObject(ShGameObject gameObject);
      void Render(Graphic::Renderer *renderer);

      void Update(const Input* input);
      void SetProjection(float width, float height);
  };
}
