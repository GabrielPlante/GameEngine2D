#include "Camera.h"

namespace ge {
	//screen + camera = world

	void Camera::zoom(double delta) {
		if (getZoom() * delta > maxZoom || getZoom() * delta < minZoom)
			return;
		const Vector2<int16_t> previousDimension{ dimension };
		dimension.x = static_cast<int16_t>(dimension.x * 1 / delta);
		dimension.y = static_cast<int16_t>(dimension.y * 1 / delta);
		move({ static_cast<double>((previousDimension.x - dimension.x)) / 2, static_cast<double>((previousDimension.y - dimension.y)) / 2 });
	}
}
