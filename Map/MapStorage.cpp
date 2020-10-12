#include "MapStorage.h"

namespace map {
	TileComponent getDefaultTile() {
		return TileComponent{};
	}
	bool isTileValid(const TileComponent& tile) {
		return tile.isInit;
	}

	ge::VectorOfVector<TileComponent> MapStorage::map{ getDefaultTile, isTileValid };
}
