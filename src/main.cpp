#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "app/application.h"
#include "graphic/renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader_program.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "model.h"

static void processInput(GLFWwindow* window, Camera &camera, float deltaTime);
static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
static ShaderProgram* loadShader(const std::string &name);
static glm::vec3 rotateAroundPoint(float angle, float radius, const glm::vec3 &position);

struct MousePositions {
  double lastX;
  double lastY;
  bool isFirstMouse;
};

MousePositions mousePositions;
Camera camera;

int main() {
  // TODO: check intitialization errors
  Application app("Engine");
  app.Init();

  Window window = app.GetWindow();

  glfwSetCursorPosCallback(window.getGlfwWindow(), mouseCallback);

  mousePositions.lastX = window.getWidth() / 2.0f;
  mousePositions.lastY = window.getHeight() / 2.0f;
  mousePositions.isFirstMouse = true;

  Graphic::Renderer* renderer = app.GetRenderer();

  // *************************************************************************

  float lastTime = 0.0f;
  float deltaTime = 0.0f;

  ShaderProgram *modelShader = loadShader("model");
  ShaderProgram *lightSourceShader = loadShader("light_source");

  ShaderProgram* shaders[] = {
    lightSourceShader,
    modelShader,
  };

  std::size_t modelsNumber = 2;

  Model *sphere = new Model("./sphere.obj");
  Model *house = new Model("./house_2/WoodenCabinObj.obj");

  house->Load();
  sphere->Load();

  Model *models = new Model[modelsNumber];
  models[0] = *sphere;
  models[1] = *house;

  glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, -15.0f);
  glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

  glm::vec3 positions[] = {
    lightPosition,
    glm::vec3(0.0f, -13.5f, -15.0f),
  };

  glm::vec3 scales[] = {
    glm::vec3(2.0f),
    glm::vec3(0.2f),
  };

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getWidth() / window.getHeight(), 1.0f, 1000.0f);

  modelShader->bind();
  modelShader->setUniformMatrix4fv("u_Projection", glm::value_ptr(projection));
  modelShader->setUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);

  for(unsigned int i = 0; i < house->getMeshes().size(); i++) {
    Mesh *mesh = house->getMeshes()[i];
    std::map<std::string, Texture*> textures = mesh->GetTextures();

    textures["texture_diffuse"]->bind(0);
    modelShader->setUniform1i("texture_diffuse", 0);

    textures["texture_specular"]->bind(1);
    modelShader->setUniform1i("texture_specular", 1);

    textures["texture_normal"]->bind(2);
    modelShader->setUniform1i("texture_normal", 2);

    modelShader->setUniform1f("material.shininess", mesh->m_Materials.shininess);
    modelShader->setUniform1f("material.specularStrength", mesh->m_Materials.shininessStrength);
  }

  lightSourceShader->bind();
  lightSourceShader->setUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);
  lightSourceShader->setUniformMatrix4fv("u_Projection", glm::value_ptr(projection));

  unsigned int activeShaderId;

  /* Loop until the user closes the window */
  while (window.isOpen()) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    unsigned int drawCallsCnt = 0;

    /* Render here */
    renderer->clear();

    processInput(window.getGlfwWindow(), camera, deltaTime);

    glm::mat4 view = camera.getViewMatrix();
    glm::vec3 cameraPosition = camera.GetPosition();

    for (unsigned int i = 0; i < 2; i++) {
      ShaderProgram* shader = shaders[i];

      shader->bind();
      shader->setUniform3f("u_CameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);
      shader->setUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
    }

    for (unsigned int i = 0; i < modelsNumber; i++) {
      ShaderProgram* shaderPr = shaders[i];

      glm::mat4 modelMat(1.0f);

      if (i == 0) {
        glm::vec3 position = rotateAroundPoint(currentTime, 15, positions[i]);
        lightPosition = position;

        modelMat = glm::translate(glm::mat4(1.0f), position);
      } else {
        modelMat = glm::translate(glm::mat4(1.0f), positions[i]);
        modelMat = glm::scale(modelMat, scales[i]);
      }

      if (activeShaderId != shaderPr->getId()) {
        shaderPr->bind();
        activeShaderId = shaderPr->getId();
      }

      shaderPr->setUniformMatrix4fv("u_View", glm::value_ptr(view));
      shaderPr->setUniformMatrix4fv("u_Model", glm::value_ptr(modelMat));

      for(unsigned int j = 0; j < models[i].getMeshes().size(); j++) {
        drawCallsCnt++;

        renderer->draw(models[i].getMeshes()[j]->GetVao(), models[i].getMeshes()[j]->GetIbo(), *shaderPr);
      }
    }

    /* Swap front and back buffers */
    window.swapBuffers();

    /* Poll for and process events */
    window.pollEvents();

    std::cout << "Time: " << deltaTime * 1000 << " ms, draw calls: " << drawCallsCnt << std::endl;
  }

  delete modelShader;
  delete lightSourceShader;

  delete sphere;
  delete house;

  return 0;
}

static glm::vec3 rotateAroundPoint(float angle, float radius, const glm::vec3 &position) {
  glm::vec3 result(1.0f, 1.0f, 1.0f);

  result.x = position.x + cos(angle) * radius;
  result.y = position.y + sin(angle) * radius;
  result.z = position.z + sin(angle) * radius;

  return result;
}

static ShaderProgram* loadShader(const std::string &name) {
  Shader modelVertexShader("./shaders/" + name + "_vertex.glsl", GL_VERTEX_SHADER);
  Shader modelFragmentShader("./shaders/" + name + "_fragment.glsl", GL_FRAGMENT_SHADER);

  ShaderProgram *modelShaders = new ShaderProgram();

  modelShaders->attach(&modelVertexShader);
  modelShaders->attach(&modelFragmentShader);
  modelShaders->link();

  return modelShaders;
}

static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
  if (mousePositions.isFirstMouse) {
    mousePositions.lastX = xpos;
    mousePositions.lastY = ypos;
    mousePositions.isFirstMouse = false;
  }

  float xoffset = xpos - mousePositions.lastX;
  float yoffset = ypos - mousePositions.lastY;

  mousePositions.lastX = xpos;
  mousePositions.lastY = ypos;

  camera.processMouseMovement(xoffset, yoffset);
}

static void processInput(GLFWwindow* window, Camera &camera, float deltaTime) {
  float offset = 5.0f * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.forward(offset);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.backward(offset);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.left(offset);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.right(offset);
  }
}
