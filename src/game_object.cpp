#include "game_object.h"

using namespace Eng;

GameObject::GameObject(const std::string &pathToFile) {
  m_Model = new Model(pathToFile);
  m_Shader = Graphic::Shader::CreateFromFile("./shaders/model.glsl");
}

GameObject::GameObject(const std::string &pathToFile, const std::string &shaderFilePath) {
  m_Model = new Model(pathToFile);
  m_Shader = Graphic::Shader::CreateFromFile(shaderFilePath);
}

GameObject::~GameObject() {
  delete m_Model;
  delete m_Shader;
}

void GameObject::Init() {
  m_Model->Load();
  m_Shader->Init();
}