#include "entity.h"
#include "components/position_component.h"

using namespace Eng;
using namespace ECS;

Entity::Entity() {
  m_Id = nextId++;
}

Entity::~Entity() {
  for(int i = 0; i < m_Components.size(); i++) {
    delete m_Components[i];
  }

  printf("Entity %i was deleted\n", m_Id);
}

int Entity::getUniqComponentId() {
  static int lastId = 0;
  return lastId++;
}