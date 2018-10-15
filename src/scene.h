#pragma once

#include "game_object.h"
#include "camera.h"
#include "graphic/renderer.h"
#include "input.h"

namespace Eng {
  class Scene {
    private:
      Camera m_Camera;
      std::vector<ShGameObject> m_GameObjects;

    public:
      Scene();
      ~Scene();

      void AddGameObject(ShGameObject gameObject);
      void Render(Graphic::Renderer *renderer);

      void Update(const Input* input);
  };
}