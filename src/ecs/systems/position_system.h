#pragma once

#include "system.h"
#include "../components/position_component.h"

namespace Eng {
  namespace ECS {
    class PositionSystem : public System {
      void Process(Entity* entity, float x, float y, float z) const;
    };
  }
}
