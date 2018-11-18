#include "position_component.h"

using namespace Eng;
using namespace ECS;

PositionComponent::PositionComponent() {}

PositionComponent::~PositionComponent() {
  printf("PositionComponent with typeId %i from entity %i was deleted\n", this->GetTypeId(), this->GetEntity()->GetId());
}