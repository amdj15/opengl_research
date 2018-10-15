#include "app/application.h"
#include "game_object.h"
#include "scene.h"

static void initScene(Eng::Scene *scene) {
  ShGameObject rect = std::make_shared<Eng::GameObject>("bunny.obj", "shaders/simple.glsl");

  scene->AddGameObject(rect);
}

int main()
{
  Application app("Engine");
  app.Init(initScene);

  app.Run();

  /* code */
  return 0;
}