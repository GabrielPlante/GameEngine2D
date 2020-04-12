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
		if (getZoom() * delta > 10 || getZoom() * delta < 0.1)
			return;
		const int previousW = camera.w, previousH = camera.h;
		camera.resize(1 / delta);
		move((previousW - camera.w) / 2, (previousH - camera.h) / 2);
		CONSOLE_LOG(std::to_string(camera.x) + " ; " + std::to_string(camera.w));
	}

	void Camera::resetZoom() {
		camera.w = originalDimensions.x;
		camera.h = originalDimensions.y;
	}
}
