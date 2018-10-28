#include "game_object.h"

using namespace Eng;

GameObject::GameObject(const std::string &pathToFile) {
  m_Model = new Model(pathToFile);
  m_Shader = Graphic::Shader::CreateFromFile("./shaders/model.glsl");
  m_Matrix = glm::mat4(1.0f);
}

GameObject::GameObject(const std::string &pathToFile, const std::string &shaderFilePath) {
  m_Model = new Model(pathToFile);
  m_Shader = Graphic::Shader::CreateFromFile(shaderFilePath);
}

GameObject::~GameObject() {
  printf("game object was deleted \n");

  delete m_Model;
  delete m_Shader;
}

void GameObject::Init() {
  m_Model->Load();
  m_Shader->Init();
}