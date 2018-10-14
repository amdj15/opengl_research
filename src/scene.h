#pragma once

#include "game_object.h"
#include "camera.h"
#include "graphic/renderer.h"

namespace Eng {
  class Scene {
    private:
      Camera m_Camera;
      std::vector<GameObject*> m_GameObjects;

    public:
      Scene();
      ~Scene();

      void AddGameObject(GameObject *gameObject);
      void Render(Graphic::Renderer *renderer);
  };
}