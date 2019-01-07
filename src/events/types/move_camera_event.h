#pragma once

#include "../event.h"

namespace Eng {
  namespace Events {
    class MoveCameraEvent : public Event {
      public:
        float xOffset;
        float yOffset;
        float sensetivity;
        float deltaTime;
        std::string direction;

        MoveCameraEvent(float xOffset, float yOffset, float sensetivity);
    };
  }
}
