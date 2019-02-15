#include "system.h"

using namespace Eng;
using namespace ECS;

void System::AddEntity(Entity *entity) {
  m_Entities.push_back(entity);
}
