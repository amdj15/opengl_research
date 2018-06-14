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
    void link() const;

    void setUniform1f(const std::string& name, float v1);
    void setUniform3f(const std::string& name, float v1, float v2, float v3);
    void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

    void setUniformMatrix4fv(const std::string& name, float *matrix_ptr);
    void setUniform1i(const std::string& name, int value);

    inline int getId() const { return m_RendererId; }

  private:
    int getUniformLocation(const std::string& name);
};
