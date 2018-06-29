#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "window.h"
#include "renderer.h"
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
  Window window(1100, 900, "Cubes");
  glfwSetCursorPosCallback(window.getGlfwWindow(), mouseCallback);

  mousePositions.lastX = window.getWidth() / 2.0f;
  mousePositions.lastY = window.getHeight() / 2.0f;
  mousePositions.isFirstMouse = true;

  Renderer renderer;

  float lastTime = 0.0f;
  float deltaTime = 0.0f;

  std::size_t modelsNumber = 4;

  Model *dragon = new Model("./dragon.obj");
  Model *cube = new Model("./cube.obj");
  Model *sphere = new Model("./sphere.obj");
  Model *man = new Model("./muro.obj");

  dragon->Load();
  cube->Load();
  sphere->Load();
  man->Load();

  Model *models = new Model[modelsNumber];
  models[0] = *sphere;
  models[1] = *dragon;
  models[2] = *cube;
  models[3] = *man;

  ShaderProgram *modelShader = loadShader("model");

  ShaderProgram* shaders[] = {
    loadShader("light_source"),
    modelShader,
    modelShader,
    modelShader
  };

  glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, -15.0f);
  glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

  glm::vec3 positions[] = {
    lightPosition,
    glm::vec3(0.0f, -13.5f, -15.0f),
    glm::vec3(-25.0f, -15.0f, -25.0f),
    glm::vec3(-10.0f, -13.5f, -20.0f),
  };

  glm::vec3 scales[] = {
    glm::vec3(2.0f),
    glm::vec3(0.5f),
    glm::vec3(50.0f, 1.0f, 50.0f),
    glm::vec3(0.03f),
  };

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getWidth() / window.getHeight(), 1.0f, 1000.0f);

  /* Loop until the user closes the window */
  while (window.isOpen()) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    std::cout << "Time: " << deltaTime * 1000 << " ms" << std::endl;

    /* Render here */
    renderer.clear();

    processInput(window.getGlfwWindow(), camera, deltaTime);

    glm::mat4 view = camera.getViewMatrix();
    glm::vec3 cameraPosition = camera.GetPosition();

    for (unsigned i = 0; i < modelsNumber; i++) {
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

      shaderPr->bind();
      shaderPr->setUniformMatrix4fv("u_View", glm::value_ptr(view));
      shaderPr->setUniformMatrix4fv("u_Projection", glm::value_ptr(projection));
      shaderPr->setUniformMatrix4fv("u_Model", glm::value_ptr(modelMat));

      shaderPr->setUniform3f("u_CameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);
      shaderPr->setUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
      shaderPr->setUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);

      for(unsigned int j = 0; j < models[i].getMeshes().size(); j++) {
        renderer.draw(models[i].getMeshes()[j].GetVao(), models[i].getMeshes()[j].GetIbo(), *shaderPr);
      }
    }

    /* Swap front and back buffers */
    window.swapBuffers();

    /* Poll for and process events */
    window.pollEvents();
  }

  for (unsigned int i = 0; i < 2; i++) {
    delete shaders[i];
  }

  delete dragon;
  delete sphere;
  delete cube;
  delete man;

  return 0;
}

static glm::vec3 rotateAroundPoint(float angle, float radius, const glm::vec3 &position) {
  glm::vec3 result(1.0f, 1.0f, 1.0f);

  result.x = position.x + cos(angle) * radius;
  result.y = position.y;
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

  // std::cout << "x, y offsetts: " << xoffset << ", " << yoffset << std::endl;

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
