#pragma once

#include <vector>
#include "shader.h"

class ShaderProgram {
  private:
    unsigned int m_RendererId;
    std::vector<Shader *> m_Shaders;
  public:
    ShaderProgram();
    ~ShaderProgram();

    void attach(const Shader *shader);
    void bind() const;
    void unbind() const;
    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void setUniform1i(const std::string& name, int value);

  private:
    int getUniformLocation(const std::string& name);
};