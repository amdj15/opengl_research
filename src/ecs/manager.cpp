#include "manager.h"
#include "../utils/logger.h"

using namespace Eng;
using namespace ECS;

Manager::Manager() {}

Manager::~Manager() {
  for(auto const &item : m_Entities) {
    delete item.second;
  }

  LOG_DEBUG("Entity manager was deleted");
}

Entity* Manager::CreateEntity() {
  Entity* entity = new Entity();
  m_Entities[entity->GetId()] = entity;

  return entity;
}

void Manager::RemoveEntity(Entity* entity) {
  m_Entities.erase(entity->GetId());
  delete entity;
}
