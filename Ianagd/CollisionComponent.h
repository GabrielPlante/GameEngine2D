#pragma once

namespace ian {
	class CollisionComponent
	{
	public:
		//The owner of this component(used for the coordinate)
		unsigned int ownerId;

		//The size of the entity
		int size{ 0 };
	};
}
