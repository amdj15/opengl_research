#include "position_component.h"
#include "../../utils/logger.h"

using namespace Eng;
using namespace ECS;

PositionComponent::PositionComponent() {}

PositionComponent::~PositionComponent() {
  LOG_DEBUG("PositionComponent with typeId {} from entity {} was deleted", this->GetTypeId(), this->GetEntity()->GetId());
}
