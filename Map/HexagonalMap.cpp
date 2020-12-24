#include "HexagonalMap.h"

#include "MapStorage.h"

/* 
 * All the work to convert coordinates is done here
 * More information here : https://www.redblobgames.com/grids/hexagons/
*/
namespace map {
	//const double tileWidth{ sqrt(3.0) * mv::tileSize };//Sqrt isn't constexpr
	//constexpr double tileHeight{ mv::tileSize * 2.0 };

	//Relative position to an absolute one (ie: from tile coordinate to real coordinate)
	ge::Vector2<long> HexagonalMap::relativeToAbsolute(ge::Vector2<size_t> relative, double tileWidth, double tileHeight) {
		return { static_cast<long>((relative.x + relative.y / 2.0) * tileWidth), static_cast<long>(relative.y * tileHeight * 3 / 4) };
	}

	//Absolute position to a relative one (ie: from real coordinate to tile coordinate)
	ge::Vector2<size_t> HexagonalMap::absoluteToRelative(ge::Vector2<double> absolute, double tileWidth, double tileHeight) {
		return { static_cast<size_t>(absolute.x / tileWidth - absolute.y * 2 / 3 / tileHeight), static_cast<size_t>(absolute.y * 4 / 3 / tileHeight) };
	}

	int HexagonalMap::distance(ge::Vector2<int> tile1, ge::Vector2<int> tile2) {
		return (abs(tile1.x - tile2.x)
			+ abs(tile1.x + tile1.y - tile2.x - tile2.y)
			+ abs(tile1.y - tile2.y)) / 2;
	}
}
