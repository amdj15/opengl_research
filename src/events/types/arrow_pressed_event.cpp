#include "arrow_pressed_event.h"

using namespace Eng;
using namespace Events;

ArrowPressedEvent::ArrowPressedEvent(Arrows arrow): m_Arrow(arrow) {}
ArrowPressedEvent::ArrowPressedEvent() {}

ArrowPressedEvent::~ArrowPressedEvent() {
  LOG_TRACE("EVENT {} was deleted", this->GetName());
}
