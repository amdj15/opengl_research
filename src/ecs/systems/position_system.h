#pragma once

#include "system.h"
#include "../components/position_component.h"
#include "../../events/arrow_pressed_event.h"
#include "../../events/dispatcher.h"

namespace Eng {
  namespace ECS {
    class PositionSystem : public System {
      public:
        PositionSystem();
        ~PositionSystem();

        void Process(SharedEvent event);
    };
  }
}
