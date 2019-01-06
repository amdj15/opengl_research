#include "arrow_pressed_event.h"

using namespace Eng;
using namespace Events;

ArrowPressedEvent::ArrowPressedEvent(Arrows arrow): m_Arrow(arrow) {}
ArrowPressedEvent::ArrowPressedEvent() {}

ArrowPressedEvent::~ArrowPressedEvent() {
  LOG_DEBUG("EVENT {} was deleted", this->GetName());
}
