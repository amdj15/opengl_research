#pragma once

#include "system.h"
#include "../components/position_component.h"
#include "../../events/arrow_pressed_event.h"
#include "../../events/dispatcher.h"

namespace Eng {
  namespace ECS {
    class MovementSystem : public System {
      public:
        MovementSystem();
        ~MovementSystem();

        void OnArrowKeyPressed(SharedEvent event);
        void Update() override;
    };
  }
}
