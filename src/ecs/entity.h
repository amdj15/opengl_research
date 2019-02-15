#pragma once

#include <bitset>
#include "components/component.h"
#include <array>

namespace Eng {
  namespace ECS {
    static int nextId = 0;

    class Entity {
      public:
        static const int MAX_COMPONENTS_LENGTH = 2;

      private:
        int m_Id;
        std::array<Component<Entity>*, MAX_COMPONENTS_LENGTH> m_Components;
        std::bitset<Entity::MAX_COMPONENTS_LENGTH> m_ComponentsBitset;

      public:
        Entity();
        ~Entity();

        inline int GetId() { return m_Id; }
        inline std::array<Component<Entity>*, MAX_COMPONENTS_LENGTH>& GetComponents() { return m_Components; }

      private:
        static int getUniqComponentId();

      public:
        template<typename T> void AddComponent() {
          T* component = new T();

          m_ComponentsBitset[getComponentTypeId<T>()] = true;
          m_Components[getComponentTypeId<T>()] = component;

          component->SetTypeId(getComponentTypeId<T>());
          component->SetEntity(this);
          component->Init();
        }

        template<typename T> int getComponentTypeId() {
          static_assert(std::is_base_of<Component<Entity>, T>::value, "must be Component subtype");

          static int typeId = getUniqComponentId();
          return typeId;
        }

      private:
        template<typename T> inline bool hasComponent() { return m_ComponentsBitset[getComponentTypeId<T>()]; }
    };
  }
}
