#include "Angle.h"

namespace ge {
	Angle::Angle(float angle)
		: angle{ angle }
	{
		if (angle < 0 || angle > 2 * PI)
			add(0);
	}

	void Angle::add(Angle delta) {
		angle += delta.get();
		while (angle < 0)
			angle += 2 * PI;
		while (angle > 2 * PI)
			angle -= 2 * PI;
	}

	void Angle::set(Angle newAngle) {
		this->angle = newAngle.get();
		if (newAngle.get() < 0 || newAngle.get() > 2 * PI)
			add(0);
	}

	float Angle::difference(const Angle other) const {
		float angleDifference = other.get() - angle;
		if (angleDifference < -PI)//Make 4 cases 2
			angleDifference += 2 * PI;
		else if (angleDifference > PI)
			angleDifference -= 2 * PI;

		return angleDifference;
	}

	bool Angle::rotate(Angle directionAngle, float rotatingSpeed, float deltaTime) {
		constexpr int multiplyingRotateFactor{ 100 };
		rotatingSpeed *= deltaTime * multiplyingRotateFactor;

		float angleDifference{ difference(directionAngle) };

		int angleSign{ angleDifference > 0 ? 1 : -1 };//Sign of the angle (1 or -1)

		if (abs(angleDifference) < rotatingSpeed) {//check if the lifeform finish rotating
			set(directionAngle);
		}
		else {
			add(rotatingSpeed * angleSign);//Rotate the correct way
		}
		if (directionAngle.get() == angle) {//If the turn is finished, we declare it as such
			return true;
		}
		return false;
	}
}
