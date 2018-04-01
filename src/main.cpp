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
  window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
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
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f
  };

  unsigned int indexes[] = {
    0, 1, 2,
    2, 3, 0
  };

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  // make and bind the VAO
  VertexArray vao;

  // vertex buffer object
  VertexBuffer vbo(positions, sizeof(positions));

  // index buffer
  IndexBuffer ibo(indexes, 6);

  VertexBufferLayout layout;
  layout.push(2); // push vertex coord layout
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

    float time = (float)glfwGetTime();

    glm::mat4 trans(1.0f);
    trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f));
    shaders.setUniformMatrix4fv("transform", glm::value_ptr(trans));

    std::cout << time << std::endl;

    textureBg.bind(0);
    shaders.setUniform1i("u_TextureBg", 0); // 0 - slot binded in texture

    textureTag.bind(1);
    shaders.setUniform1i("u_TextureTag", 1); // 1 - slot binded in texture

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
