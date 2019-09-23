#pragma once
#include <SDL.h>
#include "Angle.h"

//Find the minimum of two element
template <typename P>
P min(P arg1, P arg2) {	return arg1 > arg2 ? arg2 : arg1; }

//Find the maximum of two element
template <typename P>
P max(P arg1, P arg2) {	return arg1 < arg2 ? arg2 : arg1; }

//Everything is public in a struct if not defined
template <typename T = long int>
struct Position
{
	//The position is stocked here
	T x;
	T y;

	//Constructor taking position
	Position(T x, T y) :x{ x }, y{ y } {}

	//Constructor with a SDL_Point
	Position(const SDL_Point& point) :x{ point.x }, y{ point.y } {}

	//Default constructor
	Position() {}

	//Position to a SDL_Point
	inline SDL_Point toSDL_Point() const;

	//Find the angle between the point and the direction
	Angle angle(const Position<float> destination) const;

	//Return true if the line formed by this position and the endLinePoint intersect with the given circle
	bool lineIntersectCircle(const Position<T>& endLinePoint, const Position<>& circlePosition, int circleRadius);

	template <typename P>
	//Return true if the rectangle intersect the circle, with this position the center of the circle
	//The position x and y are the circle position and the rectangle position should be the center of the rectangle
	bool rectIntersectCircle(const Position<P>& rectanglePosition, int w, int h, int circleRadius);

	template <typename P>
	//Return the distance between two point, squared. The other point is a long
	int distanceSquared(const Position<P> destination) const { return distanceSquared(Position<float>{static_cast<float>(destination.x), static_cast<float>(destination.y)}); }

	template <typename P>
	//Operator == override
	bool operator==(const Position<P>& other) { return x == other.x && y == other.y; }
};

template <typename T>
SDL_Point Position<T>::toSDL_Point() const{
	SDL_Point point;
	point.x = static_cast<int>(x);
	point.y = static_cast<int>(y);
	return point;
}
