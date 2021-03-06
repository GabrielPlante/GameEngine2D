#pragma once
#include <chrono>

namespace ge {
	struct Clock
	{
	private:
		//Last time the clock was reset
		std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
		double timeScale{ 1 };
	public:
		//Default constructor, initialize the time at the moment the clock is constructed
		Clock() { lastTime = std::chrono::high_resolution_clock::now(); }

		//Get the time since the last reset in microseconds
		long long getTime() const { return static_cast<long long>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - lastTime).count() * timeScale); }

		//Get the time since the last reset in microseconds and reset the time
		long long resetTime() {
			auto time = getTime();
			lastTime = std::chrono::high_resolution_clock::now();
			return time;
		}

		//Set the time scale, a float number that affect the way time flow
		//It does not reset the time
		void setTimeScale(double newTimeScale) { timeScale = newTimeScale; }

		//Get the time scale
		double getTimeScale() const { return timeScale; }
	};
}