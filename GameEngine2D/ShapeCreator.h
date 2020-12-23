#pragma once
#include <memory>

#include "Vector2.h"
#include "Color.h"

namespace ge {
	//This header regroup utilitaries function to create shape
	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	class Batch;
	struct Default2DVertex;

	constexpr size_t vertexPerHexagon{ 7 };
	constexpr size_t indexPerHexagon{ 18 };

	typedef Batch<Default2DVertex, vertexPerHexagon, indexPerHexagon> HexagonBatch;

	//Create an hexagon and directly transmit it to the batch renderer, give back the id of it. The position is the position of the center
	size_t createHexagon(std::shared_ptr<Batch<Default2DVertex, vertexPerHexagon, indexPerHexagon>> batchRenderer, Vector2<float> position, float size, Color color);
}
