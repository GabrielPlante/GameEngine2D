#pragma once
#include <memory>
#include <vector>

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

	struct HexagonTransform {
		Vector2<float> position;
		float size;
		Color color;
	};

	//Create hexagons and directly transmit them to the batch renderer, give back their ids. The position is the position of the center
	std::vector<size_t> createHexagon(std::shared_ptr<HexagonBatch> batchRenderer, std::vector<HexagonTransform> hexagons);
}
