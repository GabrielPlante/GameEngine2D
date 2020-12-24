#include "PathFinder.h"

#include "MapStorage.h"

/*constexpr int maxPathSize{ 100 };

namespace map {
	bool isValid(ge::Vector2<size_t> tile) {
		MapStorage storage;
		return storage.tileExist(tile) && storage.getTile(tile).isWalkable;
	}

	std::stack<ge::Vector2<size_t>> PathFinder::makePath(const std::map<ge::Vector2<size_t>, Node>& map) const {
		size_t x{ destination.x };
		size_t y{ destination.y };

		std::stack<ge::Vector2<size_t>> path;

		while (!(map.find({ x, y })->second.parentX == x && map.find({ x, y })->second.parentY == y)
			&& map.find({ x, y })->second.x != INT_MAX && map.find({ x, y })->second.y != INT_MAX) {
			path.push(map.find({ x, y })->second.toVector2());
			size_t tempX = map.find({ x, y })->second.parentX;
			size_t tempY = map.find({ x, y })->second.parentY;
			x = tempX;
			y = tempY;
		}
		path.push(map.find({ x, y })->second.toVector2());

		return path;
	}

	std::stack<ge::Vector2<size_t>> PathFinder::findPath() const {
		//std::cout << "start : " << start.x << " ; " << start.y << " destination : " << destination.x << " ; " << destination.y << std::endl;
		std::stack<ge::Vector2<size_t>> empty;

		//If the destination is invalid, or the start and the destination are on the same tile, return the empty vector
		if (!isValid(destination) || start == destination)
			return empty;

		std::map<ge::Vector2<size_t>, Node> allMap;
		std::map<ge::Vector2<size_t>, bool> closedList;
		//The list of all position evaluated
		std::vector<Node> openList;
		//Add the starting position
		Node startNode{ start.x, start.y, start.x, start.y, 0.0, 0.0, 0.0 };
		openList.push_back(startNode);
		allMap.insert(std::pair<ge::Vector2<size_t>, Node>({ startNode.x, startNode.y }, startNode));

		//------The main loop------
		while (!openList.empty() && openList.size() < maxPathSize) {
			Node node;

			//Find the not visited valid node with the lowest cost
			do {
				//Get the node with the lowest f cost out of the open list
				float tempCost{ FLT_MAX };
				std::vector<Node>::iterator itNode;
				for (auto it = openList.begin(); it != openList.end(); it++) {
					if (it->fCost < tempCost) {
						tempCost = it->fCost;
						itNode = it;
					}
				}
				node = *itNode;
				openList.erase(itNode);

			} while (!isValid(node.toVector2()));

			//keep the information of visiting this node
			if (closedList.find({ node.x, node.y }) == closedList.end())
				closedList.insert(std::pair <ge::Vector2<size_t>, bool>({ node.x, node.y }, true));
			//Add this node to the map of all node
			//if (allMap.find({ node.x, node.y }) == allMap.end())
				//allMap.insert(std::pair <ge::Vector2<size_t>, Node>({ node.x, node.y }, node));

			for (int newX = -1; newX <= 1; newX++) {
				size_t tempX{ node.x + newX };
				for (int newY = -1; newY <= 1; newY++) {
					//Don't move in diagonal
					if (newY == newX || newY == -newX)
						continue;
					size_t tempY{ node.y + newY };
					//If this node around the current one is valid
					if (isValid({ tempX, tempY })) {
						//Add it to the all map if it is not already here
						if (allMap.find({ tempX, tempY }) == allMap.end())
							allMap.insert(std::pair<ge::Vector2<size_t>, Node>({ tempX, tempY }, { tempX, tempY, INT_MAX, INT_MAX, FLT_MAX, FLT_MAX, FLT_MAX }));
						//If it is the destination
						if (ge::Vector2<size_t>{tempX, tempY} == destination) {
							allMap.find({ tempX, tempY })->second.parentX = node.x;
							allMap.find({ tempX, tempY })->second.parentY = node.y;
							return makePath(allMap);
						}
						//If the node was never added to the closed list are if we never visited it
						else if (closedList.find({ tempX, tempY }) == closedList.end() || closedList.find({ tempX, tempY })->second == false) {
							float fNew, gNew, hNew;
							gNew = node.gCost + 1.0f;
							hNew = sqrt(calculateH({ tempX, tempY }));
							fNew = gNew + hNew;
							//If this path is better than the one we were on
							if (allMap.find({ tempX, tempY })->second.fCost == FLT_MAX || allMap.find({ tempX, tempY })->second.fCost > fNew) {
								allMap.find({ tempX, tempY })->second.fCost = fNew;
								allMap.find({ tempX, tempY })->second.hCost = hNew;
								allMap.find({ tempX, tempY })->second.gCost = gNew;
								allMap.find({ tempX, tempY })->second.parentX = node.x;
								allMap.find({ tempX, tempY })->second.parentY = node.y;
								allMap.find({ tempX, tempY })->second.x = tempX;
								allMap.find({ tempX, tempY })->second.y = tempY;
								openList.emplace_back(allMap.find({ tempX, tempY })->second);
							}
						}
					}
				}
			}
		}
		//If nothing is found, return an empty vector
		return empty;
	}
}*/
