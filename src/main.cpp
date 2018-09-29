#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "app/application.h"
#include "graphic/renderer.h"
#include "graphic/shader.h"

#include "texture.h"
#include "camera.h"
#include "model.h"

static void processInput(GLFWwindow* window, Camera &camera, float deltaTime);
static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
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

  Graphic::Shader *modelShader = Graphic::Shader::CreateFromFile("./shaders/model.glsl");
  Graphic::Shader *lightSourceShader = Graphic::Shader::CreateFromFile("./shaders/light_source.glsl");

  modelShader->Init();
  lightSourceShader->Init();

  Graphic::Shader *shaders[] = { lightSourceShader, modelShader, modelShader };

  Model *sphere = new Model("./sphere.obj");
  Model *house = new Model("./house_2/WoodenCabinObj.obj");
  Model *man = new Model("./Old_Man/muro.obj");

  house->Load();
  sphere->Load();
  man->Load();

  std::size_t modelsNumber = 3;
  Model *models = new Model[modelsNumber];

  models[0] = *sphere;
  models[1] = *house;
  models[2] = *man;

  glm::vec3 lightPosition = glm::vec3(0.0f, 7.0f, -15.0f);
  glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

  glm::vec3 positions[] = {
    lightPosition,
    glm::vec3(0.0f, -13.5f, -15.0f),
    glm::vec3(6.0f, -7.5f, -12.0f),
  };

  glm::vec3 scales[] = {
    glm::vec3(2.0f),
    glm::vec3(1.0f),
    glm::vec3(0.1f),
  };

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getWidth() / window.getHeight(), 1.0f, 1000.0f);

  modelShader->Bind();
  modelShader->SetUniformMatrix4fv("u_Projection", glm::value_ptr(projection));
  modelShader->SetUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);

  lightSourceShader->Bind();
  lightSourceShader->SetUniform3f("u_LightColor", lightColor.x, lightColor.y, lightColor.z);
  lightSourceShader->SetUniformMatrix4fv("u_Projection", glm::value_ptr(projection));

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
      Graphic::Shader *shader = shaders[i];

      shader->Bind();
      shader->SetUniform3f("u_CameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);
      shader->SetUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
    }

    for (unsigned int i = 0; i < modelsNumber; i++) {
      Graphic::Shader *shaderPr = shaders[i];

      glm::mat4 modelMat(1.0f);

      if (i == 0) {
        glm::vec3 position = rotateAroundPoint(currentTime, 15, positions[i]);
        lightPosition = position;

        modelMat = glm::translate(glm::mat4(1.0f), position);
      } else {
        modelMat = glm::translate(glm::mat4(1.0f), positions[i]);
        modelMat = glm::scale(modelMat, scales[i]);
      }

      if (activeShaderId != shaderPr->GetId()) {
        shaderPr->Bind();
        activeShaderId = shaderPr->GetId();
      }

      shaderPr->SetUniformMatrix4fv("u_View", glm::value_ptr(view));
      shaderPr->SetUniformMatrix4fv("u_Model", glm::value_ptr(modelMat));

      for(unsigned int j = 0; j < models[i].getMeshes().size(); j++) {
        drawCallsCnt++;

        if (i > 0) {
          Mesh *mesh = models[i].getMeshes()[j];
          std::map<std::string, Texture*> textures = mesh->GetTextures();

          if (textures.count("texture_diffuse") == 1) {
            textures["texture_diffuse"]->bind(0);
            shaderPr->SetUniform1i("texture_diffuse", 0);
          }

          if (textures.count("texture_specular") == 1) {
            textures["texture_specular"]->bind(1);
            shaderPr->SetUniform1i("texture_specular", 1);
          }

          if (textures.count("texture_normal") == 1) {
            textures["texture_normal"]->bind(2);
            shaderPr->SetUniform1i("texture_normal", 2);
          }

          shaderPr->SetUniform1f("material.shininess", mesh->m_Materials.shininess);
          shaderPr->SetUniform1f("material.specularStrength", mesh->m_Materials.shininessStrength);
        }

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
