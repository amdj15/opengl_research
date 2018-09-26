#pragma once

#include <string>

namespace Graphic {
  class Shader {
    protected:
      std::string m_FilePath;

    public:
      Shader(std::string filepath);
      virtual ~Shader() = default;

      static Shader* CreateFromFile(std::string filepath);

      virtual void Bind() const = 0;
      virtual void Unbind() const = 0;
      virtual void Init() = 0;
      virtual inline int GetId() const = 0;

      virtual void SetUniform1f(const std::string& name, float v1) = 0;
      virtual void SetUniform3f(const std::string& name, float v1, float v2, float v3) = 0;
      virtual void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) = 0;

      virtual void SetUniformMatrix4fv(const std::string& name, float *matrix_ptr) = 0;
      virtual void SetUniform1i(const std::string& name, int value) = 0;

    protected:
      std::string readFromFile(const std::string &resourcepath);
  };
}