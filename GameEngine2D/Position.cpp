#include "Position.h"

namespace ge {
	template <typename T>
	Angle Position<T>::angle(const Position<float> destination) const {
		constexpr float PI = 3.14159265f;
		Angle directionAngle{ static_cast<float>(atan2(-(destination.y - y), destination.x - x)) };
		if (directionAngle.get() < 0)
			directionAngle.set(std::abs(directionAngle.get()));
		else
			directionAngle.set(2 * PI - directionAngle.get());
		return directionAngle;
	}

	template <typename T>
	//http://mathworld.wolfram.com/Circle-LineIntersection.html
	bool Position<T>::lineIntersectCircle(const Position<T>& endLinePoint, const Position<>& circlePosition, int circleRadius) {
		int x1 = static_cast<int>(x - circlePosition.x);
		int y1 = static_cast<int>(y - circlePosition.y);
		int x2 = static_cast<int>(endLinePoint.x - circlePosition.x);
		int y2 = static_cast<int>(endLinePoint.y - circlePosition.y);
		return pow(circleRadius, 2) * (pow(x2 - x1, 2) + pow(y2 - y1, 2)) - pow(x1 * y2 - x2 * y1, 2) >= 0;
	}

	template <typename T>
	template <typename P>
	//https://yal.cc/rectangle-circle-intersection-test/
	bool Position<T>::rectIntersectCircle(const Position<P>& rectanglePosition, int w, int h, int circleRadius) {
		int deltaX = static_cast<int>(x - max(rectanglePosition.x, min(x, rectanglePosition.x + w)));
		int deltaY = static_cast<int>(y - max(rectanglePosition.y, min(y, rectanglePosition.x + h)));
		return (pow(deltaX, 2) + pow(deltaY, 2)) <= pow(circleRadius, 2);
	}
}
