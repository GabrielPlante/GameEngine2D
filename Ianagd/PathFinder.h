#pragma once
#include <map>
#include <stack>

#include "../GameEngine2D/Vector2.h"

namespace ian {
	//Used to find a path on the map
	class PathFinder
		//Taken from https://dev.to/jansonsa/a-star-a-path-finding-c-4a4h
	{
	private:
		//A private struct to represent a node
		struct Node {
			int x{ 0 };
			int y{ 0 };
			int parentX{ 0 };
			int parentY{ 0 };
			float gCost{ 0.0 };
			float hCost{ 0.0 };
			float fCost{ 0.0 };

			//Default constructor
			Node() {}

			//Usefull constructor
			Node(int x, int y, int parentX, int parentY, float gCost, float hCost, float fCost)
				: x{ x }, y{ y }, parentX{ parentX }, parentY{ parentY }, gCost{ gCost }, hCost{ hCost }, fCost{ fCost }
			{}

			//We need to overload "<" to put our struct into a set
			bool operator<(const Node& rhs)
			{
				return fCost < rhs.fCost;
			}

			//Get a vector2 out of this node
			ge::Vector2<int> toVector2() const { return ge::Vector2<int>{x, y}; }
		};

		//The start and the destination
		ge::Vector2<int> start;
		ge::Vector2<int> destination;

		//Calculate the H cost for a tile
		float calculateH(ge::Vector2<int> tile) const { return static_cast<float>(tile.distanceSquared(destination)); }

		//Make a path from a map of visited node
		std::stack<ge::Vector2<int>> makePath(const std::map<ge::Vector2<int>, Node>& map) const;

	public:
		//Constructor
		PathFinder(ge::Vector2<int> start, ge::Vector2<int> destination) : start{ start }, destination { destination } {}

		//Find the path between the start and the destination
		std::stack<ge::Vector2<int>> findPath() const;
	};
}

