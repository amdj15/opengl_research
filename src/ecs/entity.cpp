#include "entity.h"
#include "components/position_component.h"
#include "../utils/logger.h"

using namespace Eng;
using namespace ECS;

Entity::Entity() {
  m_Id = nextId++;
}

Entity::~Entity() {
  if (hasComponent<PositionComponent>()) {
    delete m_Components[getComponentTypeId<PositionComponent>()];
  }

  LOG_WARN("Check entity delete, need refactor! {}", m_Id);
}

int Entity::getUniqComponentId() {
  static int lastId = 0;
  return lastId++;
}
