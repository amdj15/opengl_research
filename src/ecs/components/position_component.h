#pragma once

#include "component.h"
#include "../entity.h"

namespace Eng {
  namespace ECS {
    class PositionComponent : public Component<Entity> {
      public:
        float m_X;
        float m_Y;
        float m_Z;

      public:
        PositionComponent();
        ~PositionComponent();
    };
  }
}