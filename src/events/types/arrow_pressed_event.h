#include "../event.h"

namespace Eng {
  namespace Events {
    enum class Arrows { left, right, up, down };

    class ArrowPressedEvent : public Event {
      private:
        Arrows m_Arrow;

      public:
        ArrowPressedEvent(Arrows arrow);
        ArrowPressedEvent();
        ~ArrowPressedEvent();

        inline Arrows GetArrow() { return m_Arrow; }
    };
  }
}

