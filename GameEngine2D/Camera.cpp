#include "Camera.h"

#include <GL/glew.h>

#include "Engine.h"

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	//screen + camera = world

	void Camera::updateUniform() const
	{
		Vector2<float> glTransform{ 0, 0 };
		glTransform -= static_cast<Vector2<float>>(worldRectangle.position);
		auto windowSize{ ENGINE->getWindow().getWindowSize() };
		glUniform4f(uniformIDs[0], glTransform.x, glTransform.y, static_cast<float>(currentZoom) / static_cast<float>(windowSize.x), static_cast<float>(currentZoom) / static_cast<float>(windowSize.y));
	}

	void Camera::zoom(double delta) {
		if (currentZoom * delta > maxZoom)
			currentZoom = maxZoom;
		else if (currentZoom * delta < minZoom)
			currentZoom = minZoom;
		else
			currentZoom *= delta;
		/*const Vector2<int16_t> previousDimension{ dimension };
		dimension.x = static_cast<int16_t>(dimension.x * 1 / delta);
		dimension.y = static_cast<int16_t>(dimension.y * 1 / delta);
		move({ static_cast<double>((previousDimension.x - dimension.x)) / 2, static_cast<double>((previousDimension.y - dimension.y)) / 2 });*/
	}
}
