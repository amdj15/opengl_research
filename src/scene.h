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
      glm::mat4 m_Projection;

    public:
      Scene() = default;
      ~Scene() = default;

      void AddGameObject(ShGameObject gameObject);
      void Render(Graphic::Renderer *renderer);

      void Update(const Input* input);
      void SetProjection(float width, float height);
  };
}