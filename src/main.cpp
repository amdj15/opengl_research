#include "app/application.h"
#include "game_object.h"
#include "scene.h"
#include "ecs/systems/movement_system.h"

static void initScene(Eng::Scene *scene) {
  ShGameObject chel = std::make_shared<Eng::GameObject>("chel.Obj", "shaders/simple.glsl");
  ShGameObject muroChel = std::make_shared<Eng::GameObject>("Old_Man/muro.obj", "shaders/model.glsl");
  ShGameObject home = std::make_shared<Eng::GameObject>("house_2/WoodenCabinObj.obj", "shaders/model.glsl");

  scene->AddGameObject(chel);
  scene->AddGameObject(muroChel);
  scene->AddGameObject(home);

  Eng::ECS::MovementSystem::SubscribeEntityToMoveByArrows(muroChel->GetEntity()->GetId());
}

int main()
{
  Application app("Engine");
  app.Init(initScene);

  app.Run();

  /* code */
  return 0;
}
