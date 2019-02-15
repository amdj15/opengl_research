#pragma once

#include <map>
#include "entity.h"

namespace Eng {
  namespace ECS {
    class Manager {
      private:
        std::map<int, Entity*> m_Entities;

      public:
        Manager();
        ~Manager();

        Entity* CreateEntity();
        void RemoveEntity(Entity* entity);
    };
  }
}