#include "Camera.h"

#include "../GameEngine2D/Console.h"

namespace ge {
	//screen + camera = world
	void Camera::move(int deltaX, int deltaY) {
		camera.x += deltaX;
		camera.y += deltaY;
	}

	void Camera::setPosition(Vector2<> newPos) {
		camera.x = newPos.x;
		camera.y = newPos.y;
	}

	void Camera::zoom(double delta) {
		if (getZoom() * delta > maxZoom || getZoom() * delta < minZoom)
			return;
		const int previousW = camera.w, previousH = camera.h;
		camera.resize(1 / delta);
		move((previousW - camera.w) / 2, (previousH - camera.h) / 2);
	}

	void Camera::resetZoom() {
		camera.w = originalDimensions.x;
		camera.h = originalDimensions.y;
	}
}
