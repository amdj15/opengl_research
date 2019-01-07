#include "movement_system.h"
#include "../../utils/logger.h"

using namespace Eng;
using namespace ECS;

MovementSystem::MovementSystem() {
  LOG_DEBUG("Position system was created");

  Events::Dispatcher::AddEventListener("ArrowKeyPressed", std::bind(&MovementSystem::OnArrowKeyPressed, this, std::placeholders::_1));
}

MovementSystem::~MovementSystem() {
  LOG_DEBUG("Position system was deleted");

  Events::Dispatcher::RemoveEventListener("ArrowKeyPressed", std::bind(&MovementSystem::OnArrowKeyPressed, this, std::placeholders::_1));
}

void MovementSystem::Update() {}

void MovementSystem::OnArrowKeyPressed(SharedEvent e) {
  for(auto &entity : m_Entities) {
    auto it = std::find(MovementSystem::m_MoveableEntitiesIds.begin(), MovementSystem::m_MoveableEntitiesIds.end(), entity->GetId());
    if (it == MovementSystem::m_MoveableEntitiesIds.end()) {
      continue;
    }

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
}

std::vector<int> MovementSystem::m_MoveableEntitiesIds;

void MovementSystem::SubscribeEntityToMoveByArrows(int id) {
  m_MoveableEntitiesIds.push_back(id);
}

void MovementSystem::UnsubscribeEntityToMoveByArrows(int id) {
  auto it = std::find(m_MoveableEntitiesIds.begin(), m_MoveableEntitiesIds.end(), id);

  if (it != m_MoveableEntitiesIds.end()) {
    m_MoveableEntitiesIds.erase(it);
  }
}
