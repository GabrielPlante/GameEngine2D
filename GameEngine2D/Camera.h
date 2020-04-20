#pragma once
#include <SDL.h>

#include "Rectangle.h"
#include "Vector2.h"

namespace ge {
	class Camera
	{
	private:
		double maxZoom{ 100 };
		double minZoom{ 0.01 };
		//The rectangle representing the camera
		Rectangle camera;
		Vector2<int> originalDimensions;
	public:
		//Constructor
		Camera(int x, int y, int w, int h) : Camera{ Rectangle{x, y, w, h} } {}

		//Constructor
		Camera(const Rectangle& rectangle) : camera{ rectangle }, originalDimensions{ rectangle.w, rectangle.h } {}

		//Move the camera by a offset
		void move(int deltaX, int deltaY);

		//Set a new position for the camera
		void setPosition(Vector2<> newPos);

		//Convert a position relative to the screen to a absolute in-game position
		Vector2<> relativeToAbsolute(int x, int y) const { return Vector2<>{ static_cast<long>(x / getZoom() + camera.x),
			static_cast<long>(y / getZoom() + camera.y) }; }

		//Convert a absolute in-game position to a position relative to the screen
		Vector2<> absoluteToRelative(long int x, long int y) const {
			return Vector2<>{ static_cast<long>((x - camera.x)* getZoom()),
				static_cast<long>((y - camera.y)* getZoom()) };
		}

		//Zoom by a delta
		void zoom(double delta);

		//Set a new zoom
		void resetZoom();

		//Get the current zoom
		double getZoom() const { return static_cast<double>(originalDimensions.x) / static_cast<double>(camera.w); }

		//Return true if a rectangle is in the camera. Take absolute coordinate
		bool isInCamera(const Rectangle& object) const { return camera.overlap(object); };

		//Get the rectangle that is the camera
		const Rectangle& getRectangle() const { return camera; }

		//Set a new value for the max zoom and the min zoom. The max zoom should be the greater value.
		void setMinMaxZoom(double newMinZoom, double newMaxZoom) { minZoom = newMinZoom; maxZoom = newMaxZoom; }
	};
}
