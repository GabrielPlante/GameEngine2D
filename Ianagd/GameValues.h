#pragma once

#include "../GameEngine2D/Color.h"

namespace gv {//gv as game values
	//Player related values
	constexpr long speedDividingFactor{ 1000 };

	//Map related values
	constexpr int tileSize{ 50 };
	constexpr int maxPathSize{ 1000 };//Value used to limit the A star search for a path

	//-----GAME RELATED VALUES-----

	//Value common to all wave
	constexpr long long timeBetweenWaves{ 2 * 1000 * 1000 };//In micro second
	constexpr long long timeBetweenSpawn{ 1000 * 1000 };//In micro second
	constexpr int nbrOfWave{ 3 };

	struct WaveValues {
		const int nbrOfEnemy;
		const int enemyHealth;
		const float enemySpeed;
		const ge::Color color;
		WaveValues(int nbrOfEnemy, int enemyHealth, float enemySpeed, ge::Color color)
			: nbrOfEnemy{ nbrOfEnemy }, enemyHealth{ enemyHealth }, enemySpeed{ enemySpeed }, color{ color } {}
	};

	const WaveValues wave1{ 5, 100, 0.2f, {100, 0, 0} };
	const WaveValues wave2{ 8, 100, 0.3f, {128, 80, 80} };
	const WaveValues wave3{ 2, 800, 0.2f, {255, 0, 0} };
}
