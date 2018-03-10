#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>

int main()
{
  // create the window
  sf::Window window(sf::VideoMode(800, 600), "OpenGL");

  if (glewInit() != GLEW_OK) {
    std::cout << "Oh crap!" << std::endl;
    return 1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;

  while(window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    window.display();
  }
}
