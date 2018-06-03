#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_DEPTH_TEST));

  Shader vertexShader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
  Shader fragmentShader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);

  ShaderProgram shaders;

  shaders.attach(&vertexShader);
  shaders.attach(&fragmentShader);
  shaders.link();

  Renderer renderer;

  float lastTime = 0.0f;
  float deltaTime = 0.0f;

  Model cube("./stanford-dragon.obj");
  cube.Load();

  /* Loop until the user closes the window */
  while (window.isOpen()) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    std::cout << "Time: " << deltaTime << std::endl;

    /* Render here */
    renderer.clear();

    processInput(window.getGlfwWindow(), camera, deltaTime);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getWidth() / window.getHeight(), 1.0f, 1000.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 mvp = projection * view * model;

    shaders.bind();
    shaders.setUniformMatrix4fv("mvp", glm::value_ptr(mvp));
    shaders.unbind();

    for(unsigned int i = 0; i < cube.getMeshes().size(); i++) {
      renderer.draw(cube.getMeshes()[i].GetVao(), cube.getMeshes()[i].GetIbo(), shaders);
    }

    /* Swap front and back buffers */
    window.swapBuffers();

    /* Poll for and process events */
    window.pollEvents();
  }

  return 0;
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

  std::cout << "x, y offsetts: " << xoffset << ", " << yoffset << std::endl;

  camera.processMouseMovement(xoffset, yoffset);
}

static void processInput(GLFWwindow* window, Camera &camera, float deltaTime) {
  float offset = 2.5f * deltaTime;

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
