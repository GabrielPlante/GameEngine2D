#pragma once
#include <SDL.h>

#include "Rectangle.h"
#include "Position.h"

namespace ge {
	class Camera
	{
	private:
		//The rectangle representing the camera
		Rectangle camera;
	public:
		//Constructor
		Camera(int x, int y, int w, int h);

		//Constructor
		Camera(const Rectangle& rectangle) : camera{ rectangle } {}

		//Move the camera by a offset
		void move(int deltaX, int deltaY);

		//Set a new position for the camera
		void setPosition(Position<> newPos);

		//Convert a position relative to the screen to a absolute in-game position
		Position<> relativeToAbsolute(int x, int y) const { return Position<>{ x + camera.x, y + camera.y }; }

		//Convert a absolute in-game position to a position relative to the screen
		Position<> absoluteToRelative(long int x, long int y) const { return Position<>{ x - camera.x, y - camera.y }; }

		//Zoom by a delta
		void zoom(float deltaW, float deltaH);

		//Resize by an offset
		void resize(int w, int h);

		//Return true if a rectangle is in the camera. Take absolute coordinate
		bool isInCamera(const Rectangle& object) const { return camera.overlap(object); };

		//Get the rectangle that is the camera
		const Rectangle& getRectangle() const { return camera; }
	};
}
