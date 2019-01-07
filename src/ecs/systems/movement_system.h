#pragma once

#include "system.h"
#include "../components/position_component.h"
#include "../../events/types/arrow_pressed_event.h"
#include "../../events/dispatcher.h"

namespace Eng {
  namespace ECS {
    class MovementSystem : public System {
      private:
        static std::vector<int> m_MoveableEntitiesIds;

      public:
        MovementSystem();
        ~MovementSystem();

        void OnArrowKeyPressed(SharedEvent event);
        void Update() override;

        static void SubscribeEntityToMoveByArrows(int id);
        static void UnsubscribeEntityToMoveByArrows(int id);
    };
  }
}
