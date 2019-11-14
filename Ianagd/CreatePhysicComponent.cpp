#include "CreatePhysicComponent.h"

#include "../GameEngine2D/Entity.h"

namespace ian {
	void CreatePhysicComponent::sendBackHandle(ge::ComponentHandle&& handle) const {
		entityPtr->addComponentHandle(std::move(handle));
	}
}
