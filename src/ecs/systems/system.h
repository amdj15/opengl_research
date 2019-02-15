#pragma once

#include <vector>
#include "../entity.h"

namespace Eng {
  namespace ECS {
    class System {
      protected:
        std::vector<Entity*> m_Entities;

      public:
        System() = default;
        virtual ~System() = default;

        virtual void Update() = 0;

        void AddEntity(Entity* entity);
    };
  }
}
