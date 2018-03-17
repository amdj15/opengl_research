#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_debug.h"

static unsigned int compileShader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
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

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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

  float positions[] = {
    0.0f,  0.5f, // Vertex 1 (X, Y)
    0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f // Vertex 3 (X, Y)
  };

  unsigned int buffer;
  unsigned int gVAO;

  GLCall(glGenBuffers(1, &buffer));

  GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

  // make and bind the VAO
  GLCall(glGenVertexArrays(1, &gVAO));
  GLCall(glBindVertexArray(gVAO));

  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
