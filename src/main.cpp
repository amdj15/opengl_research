#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

static unsigned int compileShader(unsigned int type, const std::string& source) {
  GLCall(unsigned int id = glCreateShader(type));
  const char* src = source.c_str();

  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int compileStatus;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus));

  if (compileStatus == GL_FALSE) {
    int logLength;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength));

    char message[logLength];
    std::string textType = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";

    GLCall(glGetShaderInfoLog(id, logLength, &logLength, message));

    std::cout << "Failed to compile " << textType << std::endl;
    std::cout << message << std::endl;

    GLCall(glDeleteShader(id));

    return 0;
  }

  return id;
}

static unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));

  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));

  return program;
}

static std::string loadShader(const std::string& filepath) {
  std::ifstream file;
  file.open(filepath);

  if (!file.is_open()) {
    throw std::runtime_error(std::string("Failed to open file: ") + filepath);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

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

  std::string vertexShaderSrc = loadShader("./shaders/vertex.glsl");
  std::string fragmentShaderSrc = loadShader("./shaders/fragment.glsl");

  unsigned int shaders = createShaders(vertexShaderSrc, fragmentShaderSrc);
  GLCall(glUseProgram(shaders));
  GLCall(unsigned int colorLocation = glGetUniformLocation(shaders, "u_Color"));

  float positions[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
  };

  unsigned int indexes[] = {
    0, 1, 2,
    2, 3, 0
  };

  // make and bind the VAO
  VertexArray vao;

  // vertex buffer object
  VertexBuffer vbo(positions, sizeof(positions));

  // index buffer
  IndexBuffer ibo(indexes, 6);

  VertexBufferLayout layout;
  layout.push(2);

  vao.addBuffer(vbo, layout);

  float red = 0.0f;
  float increment = 0.5f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GLCall(glUniform4f(colorLocation, red, 0.4f, 0.7f, 1.0f));

    ibo.bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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
