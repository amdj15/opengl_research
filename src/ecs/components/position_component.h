#pragma once

#include "component.h"
#include "../entity.h"

namespace Eng {
  namespace ECS {
    class PositionComponent : public Component<Entity> {
      public:
        float m_X{0};
        float m_Y{0};
        float m_Z{0};

      public:
        PositionComponent();
        ~PositionComponent();
    };
  }
}
