#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>

static unsigned int compileShader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();

  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int compileStatus;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == GL_FALSE) {
    int logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

    char message[logLength];
    std::string textType = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";

    glGetShaderInfoLog(id, logLength, &logLength, message);

    std::cout << "Failed to compile " << textType << std::endl;
    std::cout << message << std::endl;

    glDeleteShader(id);

    return 0;
  }

  return id;
}

static unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

static const std::string vertexShaderSrc = R"glsl(
  #version 330 core

  layout(location = 0) in vec4 position;

  void main()
  {
    gl_Position = position;
  }
)glsl";

static const std::string fragmentShaderSrc = R"glsl(
  #version 330 core

  layout(location = 0) out vec4 color;

  void main()
  {
    color = vec4(1.0, 0.0, 0.0, 1.0);
  }
)glsl";

int main() {
  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL");

  if (glewInit() != GLEW_OK) {
    std::cout << "Oh crap!" << std::endl;
    return 1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;
  std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  float positions[] = {
    0.0f,  0.5f, // Vertex 1 (X, Y)
    0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f // Vertex 3 (X, Y)
  };

  unsigned int buffer;

  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  unsigned int shaders = createShaders(vertexShaderSrc, fragmentShaderSrc);
  glUseProgram(shaders);

  while(window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.display();
  }
}
