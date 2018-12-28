#include "position_system.h"

using namespace Eng;
using namespace ECS;

void Process(Entity* entity, float x, float y, float z) {
  auto components = entity->GetComponents();
  PositionComponent* component = static_cast<PositionComponent*>(components[entity->getComponentTypeId<PositionComponent>()]);

  component->m_X = x;
  component->m_Y = y;
  component->m_Z = z;
}
