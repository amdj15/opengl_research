#include "position_system.h"
#include "../../utils/logger.h"

using namespace Eng;
using namespace ECS;

using namespace std::placeholders;

PositionSystem::PositionSystem() {
  LOG_DEBUG("Position system was created");

  Events::Dispatcher::AddEventListener("ArrowKeyPressed", std::bind(&PositionSystem::Process, this, _1));
}

PositionSystem::~PositionSystem() {
  LOG_DEBUG("Position system was deleted");
}

void PositionSystem::Process(SharedEvent e) {
  auto entity = m_Entities[0];
  auto components = entity->GetComponents();

  PositionComponent* component = static_cast<PositionComponent*>(components[entity->getComponentTypeId<PositionComponent>()]);
  auto event = std::static_pointer_cast<Events::ArrowPressedEvent>(e);

  switch(event->GetArrow()) {
    case Events::Arrows::left:
      component->m_X++;
      break;
    case Events::Arrows::right:
      component->m_X--;
      break;
    case Events::Arrows::up:
      component->m_Z++;
      break;
    case Events::Arrows::down:
      component->m_Z--;
      break;
  }
}
