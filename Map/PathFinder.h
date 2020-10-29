#pragma once
#include <stack>
#include <map>

#include "../GameEngine2D/Vector2.h"

namespace map {
	class PathFinder
	{
	private:
		//A private struct to represent a node
		struct Node {
			size_t x{ 0 };
			size_t y{ 0 };
			size_t parentX{ 0 };
			size_t parentY{ 0 };
			float gCost{ 0.0 };
			float hCost{ 0.0 };
			float fCost{ 0.0 };

			//Default constructor
			Node() {}

			//Usefull constructor
			Node(size_t x, size_t y, size_t parentX, size_t parentY, float gCost, float hCost, float fCost)
				: x{ x }, y{ y }, parentX{ parentX }, parentY{ parentY }, gCost{ gCost }, hCost{ hCost }, fCost{ fCost }
			{}

			//We need to overload "<" to put our struct into a set
			bool operator<(const Node& rhs)
			{
				return fCost < rhs.fCost;
			}

			//Get a vector2 out of this node
			ge::Vector2<size_t> toVector2() const { return ge::Vector2<size_t>{x, y}; }
		};

		//The start and the destination
		ge::Vector2<size_t> start;
		ge::Vector2<size_t> destination;

		//Calculate the H cost for a tile
		float calculateH(ge::Vector2<size_t> tile) const { return static_cast<float>(tile.distanceSquared(destination)); }

		//Make a path from a map of visited node
		std::stack<ge::Vector2<size_t>> makePath(const std::map<ge::Vector2<size_t>, Node>& map) const;

	public:
		//Constructor
		PathFinder(ge::Vector2<size_t> start, ge::Vector2<size_t> destination) : start{ start }, destination{ destination } {}

		//Find the path between the start and the destination
		std::stack<ge::Vector2<size_t>> findPath() const;
	};
}
