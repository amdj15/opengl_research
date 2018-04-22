#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader_program.h"
#include "shader.h"
#include "texture.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main() {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) {
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cout << "Oh crap!" << std::endl;
    return 1;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

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

  float red = 0.0f;
  float increment = 0.05f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    renderer.clear();

    textureBg.bind(0);
    shaders.setUniform1i("u_TextureBg", 0); // 0 - slot binded in texture

    textureTag.bind(1);
    shaders.setUniform1i("u_TextureTag", 1); // 1 - slot binded in texture

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    shaders.setUniformMatrix4fv("model", glm::value_ptr(model));
    shaders.setUniformMatrix4fv("view", glm::value_ptr(view));
    shaders.setUniformMatrix4fv("projection", glm::value_ptr(projection));

    shaders.setUniform4f("u_Color", red, 0.4f, 0.7f, 1.0f);

    renderer.draw(vao, ibo, shaders);

    if (red > 1.0f) {
      increment = -0.05f;
    } else if (red < 0) {
      increment = 0.05f;
    }

    red += increment;

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
