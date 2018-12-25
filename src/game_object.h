#pragma once
#include "graphic/shader.h"
#include "model.h"
#include "ecs/entity.h"
#include <memory>

namespace Eng {
  class GameObject {
    private:
      Graphic::Shader *m_Shader;
      Model *m_Model;
      glm::mat4 m_Matrix;
      ECS::Entity* m_Entity;

    public:
      GameObject(const std::string &pathToFile);
      GameObject(const std::string &pathToFile, const std::string &shaderFilePath);
      ~GameObject();

      void Init();

      inline Model* GetModel() const { return m_Model; }
      inline Graphic::Shader* GetShader() const { return m_Shader; }
      inline glm::mat4 GetModelMatrix() const { return m_Matrix; }
      inline void SetEntity(ECS::Entity* entity) { m_Entity = entity; }
      inline ECS::Entity* GetEntity() const { return m_Entity; }
  };
}

typedef std::shared_ptr<Eng::GameObject> ShGameObject;