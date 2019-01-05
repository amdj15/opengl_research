#include "arrow_pressed_event.h"

using namespace Eng;
using namespace Events;

ArrowPressedEvent::ArrowPressedEvent(Arrows arrow): Event("arrow_pressed"), m_Arrow(arrow) {}
ArrowPressedEvent::ArrowPressedEvent(): Event("arrow_pressed") {}

ArrowPressedEvent::~ArrowPressedEvent() {
  LOG_DEBUG("EVENT {} was deleted", this->GetName());
}
