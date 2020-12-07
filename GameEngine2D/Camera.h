#pragma once

#include "UniformHandler.h"
#include "Vector2.h"

namespace ge {
	class Camera
		: public UniformHandler
	{
	private:
		double maxZoom{ 100 };
		double minZoom{ 0.01 };
		//The rectangle representing the camera
		//Rectangle camera;
		Vector2<int> originalDimensions;

		Vector2<double> position;
		Vector2<int16_t> dimension;
	public:
		//Constructor
		Camera(Vector2<double> position, Vector2<int16_t> dimension, double maxZoom = 100, double minZoom = 0.01)
			: UniformHandler{ "u_Position" }, position { position }, dimension{ dimension }, originalDimensions{ dimension }, maxZoom{ maxZoom }, minZoom{ minZoom }
		{}

		//Update the uniform associated with the camera
		void updateUniform() const override;

		//Move the camera by a offset
		void move(Vector2<double> offset) { position += offset; }

		//Set a new position for the camera
		void setPosition(Vector2<double> newPos) { position = newPos; }

		//Convert a position relative to the screen to a absolute in-game position
		Vector2<double> relativeToAbsolute(Vector2<int16_t> relativePos) const
		{ return Vector2<double>{ relativePos.x / getZoom() + position.x, relativePos.y / getZoom() + position.y }; }

		//Convert a absolute in-game position to a position relative to the screen
		Vector2<int16_t> absoluteToRelative(Vector2<double> absolutePos) const {
			return Vector2<int16_t>{ static_cast<int16_t>((absolutePos.x - position.x)* getZoom()),
				static_cast<int16_t>((absolutePos.y - position.y)* getZoom()) };
		}

		Vector2<float> relativeToOpenGL(Vector2<int16_t>) const {
			//return Vector2<float>{}
		}

		//Zoom by a delta
		void zoom(double delta);

		//Set a new zoom
		void resetZoom() { dimension = originalDimensions; }

		//Get the current zoom
		double getZoom() const { return static_cast<double>(originalDimensions.x) / static_cast<double>(dimension.x); }

		//Return true if a rectangle is in the camera. Take absolute coordinate
		//bool isInCamera(const Rectangle& object) const { return camera.overlap(object); };

		//Set a new value for the max zoom and the min zoom. The max zoom should be the greater value.
		void setMinMaxZoom(double newMinZoom, double newMaxZoom) { minZoom = newMinZoom; maxZoom = newMaxZoom; }
	};
}
