#pragma once

namespace Eng {
  namespace ECS {
    template<typename T> class Component {
      private:
        T *m_Entity;
        int m_TypeId{-1};

      public:
        virtual ~Component() = default;

        virtual void Init() {};

        inline void SetTypeId(int typeId) { m_TypeId = typeId; }
        inline int GetTypeId() const { return m_TypeId; }

        inline void SetEntity(T* entity) { m_Entity = entity; }
        inline T* GetEntity() const { return m_Entity; }
    };
  }
}