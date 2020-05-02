#pragma once

namespace ian {

	constexpr int interWave{ -1 };
	constexpr int waveInProgress{ 0 };
	constexpr int goForNextWave{ 1 };
	constexpr int playerLost{ 2 };
	constexpr int playerWin{ 3 };

	//This component hold every object global to the game
	class GameComponent
	{
	public:
		int playerGold{ 0 };

		//-1 == Asking, 0 == wave running, 1 == Go, 2 == lost, 3 == win
		int startNewWave{ -1 };

		unsigned int starterUiId{ 0 };
	};
}
