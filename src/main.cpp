#include "app/application.h"
#include "game_object.h"
#include "scene.h"

static void initScene(Eng::Scene *scene) {
  ShGameObject chel = std::make_shared<Eng::GameObject>("chel.Obj", "shaders/simple.glsl");
  ShGameObject lamp = std::make_shared<Eng::GameObject>("sphere.obj", "shaders/light_source.glsl");
  ShGameObject bunny = std::make_shared<Eng::GameObject>("bunny.obj", "shaders/simple.glsl");
  ShGameObject drag = std::make_shared<Eng::GameObject>("dragon.obj", "shaders/simple.glsl");

  scene->AddGameObject(chel);
  scene->AddGameObject(lamp);
  scene->AddGameObject(bunny);
  scene->AddGameObject(drag);
}

int main()
{
  Application app("Engine");
  app.Init(initScene);

  app.Run();

  /* code */
  return 0;
}