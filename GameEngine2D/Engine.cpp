#include "Engine.h"
//Size of the screen
constexpr int SCREEN_WIDTH{ 1200 };
constexpr int SCREEN_HEIGHT{ 600 };

long long Engine::timestep() {
	long long timeSinceLastReset = engineClock.resetTime();
	timeSinceStart += timeSinceLastReset;
	return timeSinceLastReset;
}

void Engine::init() {

}
