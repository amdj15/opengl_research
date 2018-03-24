#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"
#include "renderer.h"

Shader::Shader(std::string filepath, unsigned int type): m_Filepath(filepath), m_Type(type) {
  m_Source = loadShader(filepath);

  compileShader();
}

Shader::~Shader() {
  std::cout << "Delete shader: " << m_RendererId << std::endl;

  GLCall(glDeleteShader(m_RendererId));
}

std::string Shader::loadShader(const std::string& filepath) {
  std::ifstream file;
  file.open(filepath);

  if (!file.is_open()) {
    throw std::runtime_error(std::string("Failed to open file: ") + filepath);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

void Shader::compileShader() {
  GLCall(m_RendererId = glCreateShader(m_Type));
  const char* src = m_Source.c_str();

  GLCall(glShaderSource(m_RendererId, 1, &src, nullptr));
  GLCall(glCompileShader(m_RendererId));

  int compileStatus;
  GLCall(glGetShaderiv(m_RendererId, GL_COMPILE_STATUS, &compileStatus));

  if (compileStatus == GL_FALSE) {
    int logLength;
    GLCall(glGetShaderiv(m_RendererId, GL_INFO_LOG_LENGTH, &logLength));

    char message[logLength];
    std::string textType = (m_Type == GL_VERTEX_SHADER) ? "vertex" : "fragment";

    GLCall(glGetShaderInfoLog(m_RendererId, logLength, &logLength, message));

    std::cout << "Failed to compile " << textType << std::endl;
    std::cout << message << std::endl;
  }
}
