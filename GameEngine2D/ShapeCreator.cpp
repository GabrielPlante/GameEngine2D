#include "ShapeCreator.h"

#include "Default2DVertex.h"
#include "Batch.h"

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	std::vector<size_t> createHexagon(std::shared_ptr<HexagonBatch> batchRenderer, std::vector<HexagonTransform> hexagons)
	{
		//How to represent an hexagon : 6 triangles composed of the center and two adjacents vertex

		std::vector<std::array<Default2DVertex, vertexPerHexagon>> vertexesVector;
		std::vector<std::array<unsigned int, indexPerHexagon>> indexesVector;

		//Index array is the same for each hexagon
		std::array<unsigned int, indexPerHexagon> indexArray{
				0, 1, 2,
				0, 2, 3,
				0, 3, 4,
				0, 4, 5,
				0, 5, 6,
				0, 6, 1
		};

		for (auto hexagon : hexagons) {

			const double hexagonWidth{ 1.73205081 * hexagon.size }; //sqrt(3) * size
			const double hexagonHeight{ 2 * hexagon.size };

			const std::array<Vector2<double>, 6> vertexPosition{//Starting at the top vertex and going clockwise
				//An hexagon has a vertical and horizontal symetry so coordinate inversion doesn't affect it
				Vector2<double>{hexagon.position.x, hexagon.position.y + hexagonHeight / 2},
				Vector2<double>{hexagon.position.x + hexagonWidth / 2, hexagon.position.y + hexagonHeight / 4},
				Vector2<double>{hexagon.position.x + hexagonWidth / 2, hexagon.position.y - hexagonHeight / 4},
				Vector2<double>{hexagon.position.x, hexagon.position.y - hexagonHeight / 2},
				Vector2<double>{hexagon.position.x - hexagonWidth / 2, hexagon.position.y - hexagonHeight / 4},
				Vector2<double>{hexagon.position.x - hexagonWidth / 2, hexagon.position.y + hexagonHeight / 4},
			};

			std::array<Default2DVertex, vertexPerHexagon> vertexArray{
				Default2DVertex{hexagon.position, hexagon.color},
				Default2DVertex{vertexPosition[0], hexagon.color},
				Default2DVertex{vertexPosition[1], hexagon.color},
				Default2DVertex{vertexPosition[2], hexagon.color},
				Default2DVertex{vertexPosition[3], hexagon.color},
				Default2DVertex{vertexPosition[4], hexagon.color},
				Default2DVertex{vertexPosition[5], hexagon.color},
			};

			vertexesVector.push_back(vertexArray);
			indexesVector.push_back(indexArray);
		}

		//Create the hexagons in the batch renderer and return their ids
		return batchRenderer->addObject(vertexesVector, indexesVector);
	}
}