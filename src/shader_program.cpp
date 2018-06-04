#include <GL/glew.h>
#include "shader_program.h"
#include "renderer.h"

ShaderProgram::ShaderProgram() {
  GLCall(m_RendererId = glCreateProgram());
}

ShaderProgram::~ShaderProgram() {
  GLCall(glDeleteProgram(m_RendererId));
}

void ShaderProgram::attach(const Shader *shader) {
  GLCall(glAttachShader(m_RendererId, shader->getId()));

  // TODO: research delete shader after attach
  // GLCall(glDeleteShader(shader->getId()));
  // GLCall(glDeleteShader(fs));
}

void ShaderProgram::bind() const {
  GLCall(glUseProgram(m_RendererId));
}

void ShaderProgram::unbind() const {
  GLCall(glUseProgram(0));
}

void ShaderProgram::link() const {
  GLCall(glLinkProgram(m_RendererId));
  GLCall(glValidateProgram(m_RendererId));
}

void ShaderProgram::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) {
  int location = getUniformLocation(name);

  GLCall(glUniform4f(location, v1, v2, v3, v4));
}

void ShaderProgram::setUniform3f(const std::string& name, float v1, float v2, float v3) {
  GLCall(glUniform3f(getUniformLocation(name), v1, v2, v3));
}

void ShaderProgram::setUniformMatrix4fv(const std::string& name, float *matrix_ptr) {
  int location = getUniformLocation(name);
  GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, matrix_ptr));
}

void ShaderProgram::setUniform1i(const std::string& name, int value) {
  GLCall(glUniform1i(getUniformLocation(name), value));
}

int ShaderProgram::getUniformLocation(const std::string& name) {
  GLCall(return glGetUniformLocation(m_RendererId, name.c_str()));
}
