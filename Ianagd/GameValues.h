#pragma once

namespace gv {//gv as game values
	//Player related values
	constexpr long speedDividingFactor{ 1000 };

	//Map related values
	constexpr int tileSize{ 50 };
	constexpr int maxPathSize{ 1000 };//Value used to limit the A star search for a path

	//-----GAME RELATED VALUES-----

	//Value common to all wave
	constexpr long long timeBetweenWaves{ 10 * 1000 * 1000 };//In micro second
	constexpr long long timeBetweenSpawn{ 1000 * 1000 };//In micro second

	//Value of wave 1

}
