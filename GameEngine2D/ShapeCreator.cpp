#include "ShapeCreator.h"

#include "Default2DVertex.h"
#include "Batch.h"

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	size_t createHexagon(std::shared_ptr<Batch<Default2DVertex, vertexPerHexagon, indexPerHexagon>> batchRenderer, Vector2<float> position, float size, Color color)
	{
		//How to represent an hexagon : 6 triangles composed of the center and two adjacents vertex

		const double hexagonWidth{ 1.73205081 * size }; //sqrt(3) * size
		const double hexagonHeight{ 2 * size };

		const std::array<Vector2<double>, 6> vertexPosition{//Starting at the top vertex and going clockwise
			//An hexagon has a vertical and horizontal symetry so coordinate inversion doesn't affect it
			Vector2<double>{position.x, position.y + hexagonHeight / 2},
			Vector2<double>{position.x + hexagonWidth / 2, position.y + hexagonHeight / 4},
			Vector2<double>{position.x + hexagonWidth / 2, position.y - hexagonHeight / 4},
			Vector2<double>{position.x, position.y - hexagonHeight / 2},
			Vector2<double>{position.x - hexagonWidth / 2, position.y - hexagonHeight / 4},
			Vector2<double>{position.x - hexagonWidth / 2, position.y + hexagonHeight / 4},
		};

		std::array<Default2DVertex, vertexPerHexagon> vertexArray{
			Default2DVertex{position, color},
			Default2DVertex{vertexPosition[0], color},
			Default2DVertex{vertexPosition[1], color},
			Default2DVertex{vertexPosition[2], color},
			Default2DVertex{vertexPosition[3], color},
			Default2DVertex{vertexPosition[4], color},
			Default2DVertex{vertexPosition[5], color},
		};

		std::array<unsigned int, indexPerHexagon> indexArray{
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 1
		};

		//Create the hexagon in the batch renderer and return the id
		return batchRenderer->addObject({ vertexArray }, { indexArray })[0];
	}
}