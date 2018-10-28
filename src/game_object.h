#pragma once
#include "graphic/shader.h"
#include "model.h"
#include <memory>

namespace Eng {
  class GameObject {
    private:
      Graphic::Shader *m_Shader;
      Model *m_Model;
      glm::mat4 m_Matrix;

    public:
      GameObject(const std::string &pathToFile);
      GameObject(const std::string &pathToFile, const std::string &shaderFilePath);
      ~GameObject();

      void Init();

      inline Model* GetModel() const { return m_Model; }
      inline Graphic::Shader* GetShader() const { return m_Shader; }
      inline glm::mat4 GetModelMatrix() const { return m_Matrix; }
  };
}

typedef std::shared_ptr<Eng::GameObject> ShGameObject;