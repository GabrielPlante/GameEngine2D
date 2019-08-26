#include "Engine.h"

long long Engine::timestep() {
	long long timeSinceLastReset = engineClock.resetTime();
	timeSinceStart += timeSinceLastReset;
	return timeSinceLastReset;
}
