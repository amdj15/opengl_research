#include "common.h"
#include "shader.h"
#include <iostream>

using namespace Devices;
using namespace OpenGL;

Shader::Shader(std::string filepath): Graphic::Shader(filepath) {
  GLCall(m_RendererId = glCreateProgram());
}

Shader::~Shader() {
  GLCall(glDeleteProgram(m_RendererId));

  for(size_t i = 0; i < m_ShadersLength; i++)
  {
    GLCall(glDeleteShader(m_ShadersIds[i]));
  }
}

void Shader::Init() {
  unsigned int position = m_FilePath.find_last_of('/');
  std::string directory = m_FilePath.substr(0, position);
  std::string filename = m_FilePath.substr(position + 1);

  m_VertexSource = readFromFile(directory + "/vertex_" + filename);
  m_FragmentSource = readFromFile(directory + "/fragment_" + filename);

  m_ShadersIds[0] = compile(m_VertexSource, GL_VERTEX_SHADER);
  m_ShadersIds[1] = compile(m_FragmentSource, GL_FRAGMENT_SHADER);

  for(unsigned int i = 0; i < m_ShadersLength ; i++) {
    GLCall(glAttachShader(m_RendererId, m_ShadersIds[i]));
  }

  GLCall(glLinkProgram(m_RendererId));
  GLCall(glValidateProgram(m_RendererId));
}

void Shader::Bind() const {
  GLCall(glUseProgram(m_RendererId));
}

void Shader::Unbind() const {
  GLCall(glUseProgram(0));
}

unsigned int Shader::compile(const std::string &source, unsigned int type) {
  const char *src = source.c_str();

  GLCall(unsigned int shaderId = glCreateShader(type));
  GLCall(glShaderSource(shaderId, 1, &src, nullptr));
  GLCall(glCompileShader(shaderId));

  int status;
  GLCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status));

  if (status == GL_FALSE) {
    int logLength;
    GLCall(glGetShaderiv(m_RendererId, GL_INFO_LOG_LENGTH, &logLength));

    char message[logLength];
    std::string textType = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
    GLCall(glGetShaderInfoLog(m_RendererId, logLength, &logLength, message));

    std::cout << "Failed to compile " << textType << std::endl;
    std::cout << message << std::endl;
    throw std::runtime_error("Failed to compile shader");
  }

  return shaderId;
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) {
  int location = getUniformLocation(name);

  GLCall(glUniform4f(location, v1, v2, v3, v4));
}

void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3) {
  int location = getUniformLocation(name);

  if (location > -1) {
    GLCall(glUniform3f(location, v1, v2, v3));
  }
}

void Shader::SetUniform1f(const std::string& name, float v1) {
  int location = getUniformLocation(name);

  if (location > -1) {
    GLCall(glUniform1f(location, v1));
  }
}

void Shader::SetUniformMatrix4fv(const std::string& name, float *matrix_ptr) {
  int location = getUniformLocation(name);
  GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, matrix_ptr));
}

void Shader::SetUniform1i(const std::string& name, int value) {
  GLCall(glUniform1i(getUniformLocation(name), value));
}

int Shader::getUniformLocation(const std::string& name) {
  GLCall(return glGetUniformLocation(m_RendererId, name.c_str()));
}
