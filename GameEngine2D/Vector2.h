#pragma once
#include <vector>

#include "Angle.h"

namespace ge {
	//Find the minimum of two element
	template <typename P>
	P min(P arg1, P arg2) { return arg1 > arg2 ? arg2 : arg1; }

	//Find the maximum of two element
	template <typename P>
	P max(P arg1, P arg2) { return arg1 < arg2 ? arg2 : arg1; }

	//Everything is public in a struct if not defined
	template <typename T = long int>
	struct Vector2
	{
		//The position is stocked here
		T x;
		T y;

		//Constructor taking position
		constexpr Vector2(T x, T y) :x{ x }, y{ y } {}

		//Default constructor
		constexpr Vector2() {}

		//Find the angle between the point and the direction
		Angle angle(const Vector2<> destination) const;

		//Return true if the line formed by this position and the endLinePoint intersect with the given circle
		bool lineIntersectCircle(const Vector2<T>& endLinePoint, const Vector2<>& circlePosition, int circleRadius);

		template <typename P>
		//Return true if the rectangle intersect the circle, with this position the center of the circle
		//The position x and y are the circle position and the rectangle position should be the center of the rectangle
		bool rectIntersectCircle(const Vector2<P>& rectanglePosition, int w, int h, int circleRadius);

		template <typename P>
		//Return the distance between two point, squared. The other point is a long
		P distanceSquared(const Vector2<P> destination) const { return static_cast<P>(pow(x - destination.x, 2) + pow(y - destination.y, 2)); }

		template <typename P>
		//Operator == override
		bool operator==(const Vector2<P>& other) const { return x == other.x && y == other.y; }

		template <typename P>
		//Operator != override
		bool operator!=(const Vector2<P>& other) const { return x != other.x || y != other.y; }

		template <typename P>
		//Add two position
		void operator+=(const Vector2<P>& other) { x += other.x; y += other.y; }
		template <typename P>
		void operator-=(const Vector2<P>& other) { x -= other.x; y -= other.y; }

		template <typename P>
		//Multiply two position
		void operator*=(const Vector2<P>& other) { x *= other.x; y *= other.y; }
		template <typename P>
		void operator*=(P constant) { x *= constant; y *= constant; }

		template <typename P>
		//Operator < override for map
		bool operator<(const Vector2<P>& other) const {
			return x != other.x ? x < other.x : y < other.y;
		}

		//Overloading of the type cast, so static_cast can be used on the Vector2D
		template <typename P>
		operator Vector2<P>() const {
			return Vector2<P>{static_cast<P>(x), static_cast<P>(y)};
		}
	};


	template <typename T>
	//Push a position in a vector
	void operator<<(std::vector<T>& vector, const Vector2<T>& position) {
		vector.push_back(position.x);
		vector.push_back(position.y);
	}

	template <typename T>
	//Extract a position of a vector
	void operator>>(std::vector<T>& vector, Vector2<T>& position) {
		position.y = vector.back();
		vector.pop_back();
		position.x = vector.back();
		vector.pop_back();
	}

	template <typename T>
	Angle Vector2<T>::angle(const Vector2<> destination) const {
		Angle directionAngle{ static_cast<float>(atan2(-(destination.y - y), destination.x - x)) };
		if (directionAngle.get() < 0)
			directionAngle.set(std::abs(directionAngle.get()));
		else
			directionAngle.set(2 * PI - directionAngle.get());
		return directionAngle;
	}

	template <typename T>
	//http://mathworld.wolfram.com/Circle-LineIntersection.html
	bool Vector2<T>::lineIntersectCircle(const Vector2<T>& endLinePoint, const Vector2<>& circlePosition, int circleRadius) {
		int x1 = static_cast<int>(x - circlePosition.x);
		int y1 = static_cast<int>(y - circlePosition.y);
		int x2 = static_cast<int>(endLinePoint.x - circlePosition.x);
		int y2 = static_cast<int>(endLinePoint.y - circlePosition.y);
		return pow(circleRadius, 2) * (pow(x2 - x1, 2) + pow(y2 - y1, 2)) - pow(x1 * y2 - x2 * y1, 2) >= 0;
	}

	template <typename T>
	template <typename P>
	//https://yal.cc/rectangle-circle-intersection-test/
	bool Vector2<T>::rectIntersectCircle(const Vector2<P>& rectanglePosition, int w, int h, int circleRadius) {
		int deltaX = static_cast<int>(x - max(rectanglePosition.x, min(x, rectanglePosition.x + w)));
		int deltaY = static_cast<int>(y - max(rectanglePosition.y, min(y, rectanglePosition.x + h)));
		return (pow(deltaX, 2) + pow(deltaY, 2)) <= pow(circleRadius, 2);
	}

	template <typename T, const int primeConstant>
	struct Vector2Hash {
		std::size_t operator()(const Vector2<T>& v) const {
			return (primeConstant + v.x) * primeConstant + v.y;
		}
	};

}
