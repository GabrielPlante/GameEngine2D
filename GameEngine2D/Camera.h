#pragma once

#include "UniformHandler.h"
#include "Vector2.h"

namespace ge {
	struct CameraRectangle {
		Vector2<double> position;
		Vector2<int16_t> dimension;
	};

	//All position are relative to the center of the rectangle
	class Camera
		: public UniformHandler
	{
	private:
		double maxZoom{ 100 };
		double minZoom{ 0.01 };

		double currentZoom{ 1 };

		CameraRectangle worldRectangle;
		CameraRectangle screenRectangle;

		Vector2<int16_t> screenSize;
	public:
		//Constructor
		Camera(CameraRectangle worldRectangle, Vector2<int16_t> screenSize, CameraRectangle screenRectangle = { {0, 0}, {0, 0} }, double maxZoom = 100, double minZoom = 0.01)
			: UniformHandler{ "u_CameraPosition" }, worldRectangle{ worldRectangle }, screenSize{ screenSize }, screenRectangle{ screenRectangle }, maxZoom{ maxZoom }, minZoom{ minZoom }
		{}

		//Update the uniform associated with the camera
		void updateUniform() const override;

		//Move the camera by a offset
		void move(Vector2<double> offset) { worldRectangle.position += offset * (1 / currentZoom); }

		//Set a new position for the camera
		void setPosition(Vector2<double> newPos) { worldRectangle.position = newPos; }

		//Convert a position relative to the screen to a absolute in-game position
		Vector2<double> relativeToAbsolute(Vector2<int16_t> relativePos) const
		{ return Vector2<double>{ relativePos.x / getZoom() + worldRectangle.position.x, relativePos.y / getZoom() + worldRectangle.position.y }; }

		//Convert a absolute in-game position to a position relative to the screen
		Vector2<int16_t> absoluteToRelative(Vector2<double> absolutePos) const {
			return Vector2<int16_t>{ static_cast<int16_t>((absolutePos.x - worldRectangle.position.x)* getZoom()),
				static_cast<int16_t>((absolutePos.y - worldRectangle.position.y)* getZoom()) };
		}

		//Zoom by a delta
		void zoom(double delta);

		//Set a new zoom
		void resetZoom() { currentZoom = 1; }

		//Get the current zoom
		double getZoom() const { return currentZoom; }

		//Return true if a rectangle is in the camera. Take absolute coordinate
		//bool isInCamera(const Rectangle& object) const { return camera.overlap(object); };

		//Set a new value for the max zoom and the min zoom. The max zoom should be the greater value.
		void setMinMaxZoom(double newMinZoom, double newMaxZoom) { minZoom = newMinZoom; maxZoom = newMaxZoom; }
	};
}
