#include "Camera.h"

#include <GL/glew.h>

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	//screen + camera = world

	void Camera::updateUniform() const
	{
		Vector2<float> glTransform{ screenRectangle.position };
		glTransform -= static_cast<Vector2<float>>(worldRectangle.position);
		glUniform3f(uniformID, glTransform.x, glTransform.y, static_cast<float>(currentZoom));
	}

	void Camera::zoom(double delta) {
		if (currentZoom * delta > maxZoom || currentZoom * delta < minZoom)
			return;
		currentZoom *= delta;
		/*const Vector2<int16_t> previousDimension{ dimension };
		dimension.x = static_cast<int16_t>(dimension.x * 1 / delta);
		dimension.y = static_cast<int16_t>(dimension.y * 1 / delta);
		move({ static_cast<double>((previousDimension.x - dimension.x)) / 2, static_cast<double>((previousDimension.y - dimension.y)) / 2 });*/
	}
}
