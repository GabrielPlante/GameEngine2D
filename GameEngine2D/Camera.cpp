#include "Camera.h"

namespace ge {
	//screen + camera = world
	Camera::Camera(int x, int y, int w, int h)
		:camera{ x, y, w, h }
	{
	}

	void Camera::move(int deltaX, int deltaY) {
		camera.x += deltaX;
		camera.y += deltaY;
	}

	void Camera::setPosition(Vector2<> newPos) {
		camera.x = newPos.x;
		camera.y = newPos.y;
	}

	void Camera::zoom(float deltaW, float deltaH) {
		camera.w = static_cast<int>(camera.w * deltaW);
		camera.h = static_cast<int>(camera.h * deltaH);
	}

	void Camera::resize(int w, int h) {
		camera.w = w;
		camera.h = h;
	}
}
