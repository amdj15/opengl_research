#pragma once

#include <bitset>
#include "components/component.h"
#include <vector>

namespace Eng {
  namespace ECS {
    static int nextId = 0;

    class Entity {
      public:
        static const int MAX_COMPONENTS_LENGTH = 2;

      private:
        int m_Id;
        std::vector<Component<Entity>*> m_Components;
        std::bitset<Entity::MAX_COMPONENTS_LENGTH> m_ComponentsBitset;

      public:
        Entity();
        ~Entity();

        inline int GetId() { return m_Id; }

      private:
        static int getUniqComponentId();

      public:
        template<typename T> void AddComponent() {
          T* component = new T();

          m_ComponentsBitset[getComponentTypeId<T>()] = true;
          m_Components.push_back(component);

          component->SetTypeId(getComponentTypeId<T>());
          component->SetEntity(this);
          component->Init();
        }

      private:
        template<typename T> inline bool hasComponent() const { return m_ComponentsBitset[getComponentTypeId<T>()]; }

        template<typename T> int getComponentTypeId() {
          static_assert(std::is_base_of<Component<Entity>, T>::value, "must be Component subtype");

          static int typeId = getUniqComponentId();
          return typeId;
        }
    };
  }
}