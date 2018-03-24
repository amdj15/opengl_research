#pragma once

#include <string>

class Shader {
  private:
    std::string m_Filepath;
    unsigned int m_Type;
    std::string m_Source;
    unsigned int m_RendererId;

  public:
    Shader(std::string filepath, unsigned int type);
    ~Shader();

    inline unsigned int getId() const {
      return m_RendererId;
    }

  private:
    void compileShader();
    std::string loadShader(const std::string& filepath);
};
