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

void processInput(GLFWwindow* window, Camera &camera);

int main() {
  float positions[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
    0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
    0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
    0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
    0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
  };

  unsigned int indexes[] = {
    // front
    0, 3, 2,
    2, 1, 0,
    // back
    4, 5, 6,
    6, 7 ,4,
    // left
    11, 8, 9,
    9, 10, 11,
    // right
    12, 13, 14,
    14, 15, 12,
    // bottom
    16, 17, 18,
    18, 19, 16,
    // top
    20, 21, 22,
    22, 23, 20
  };

  // TODO: check intitialization errors
  Window window(800, 600, "Cubes");

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_DEPTH_TEST));

  // index buffer
  IndexBuffer ibo(indexes, 36);

  // make and bind the VAO
  VertexArray vao;

  // vertex buffer object
  VertexBuffer vbo(positions, sizeof(positions));

  VertexBufferLayout layout;
  layout.push(3); // push vertex coord layout
  layout.push(2); // push textrurs coord layout

  vao.addBuffer(vbo, layout);

  Shader vertexShader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
  Shader fragmentShader("./shaders/fragment.glsl", GL_FRAGMENT_SHADER);

  ShaderProgram shaders;

  shaders.attach(&vertexShader);
  shaders.attach(&fragmentShader);

  shaders.bind();

  Texture textureBg("./textures/wall.png");
  Texture textureTag("./textures/tag.png");

  Renderer renderer;

  Camera camera;

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };

  /* Loop until the user closes the window */
  while (window.isOpen()) {
    /* Render here */
    renderer.clear();

    textureBg.bind(0);
    shaders.setUniform1i("u_TextureBg", 0); // 0 - slot binded in texture

    textureTag.bind(1);
    shaders.setUniform1i("u_TextureTag", 1); // 1 - slot binded in texture

    processInput(window.getGlfwWindow(), camera);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getWidth() / window.getHeight(), 0.1f, 100.0f);

    shaders.setUniformMatrix4fv("projection", glm::value_ptr(projection));
    shaders.setUniformMatrix4fv("view", glm::value_ptr(view));

    for (int i = 0; i < 10; i++) {
      glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);

      float angle = (i % 3 == 0) ? glfwGetTime() * 25.0f * (i + 1) : 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(-0.5f, 1.0f, 0.0f));

      shaders.setUniformMatrix4fv("model", glm::value_ptr(model));

      renderer.draw(vao, ibo, shaders);
    }

    /* Swap front and back buffers */
    window.swapBuffers();

    /* Poll for and process events */
    window.pollEvents();
  }

  return 0;
}

void processInput(GLFWwindow* window, Camera &camera) {
  float offset = 0.05f;

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
