#pragma once
#include <cmath>
constexpr float PI = 3.14159265f;

//An angle is a float between 0 and 2*PI
struct Angle
{
private:
	//The angle is private because adding angle is non-trivial
	float angle;
public:
	//Default constructor
	Angle(float angle = 0) : angle{ angle } {
		if (angle < 0 || angle > 2 * PI)
			add(0);
	}

	//Add (or substract) an angle to change the angle
	void add(Angle delta) {
		angle += delta.get();
		while (angle < 0)
			angle += 2 * PI;
		while (angle > 2 * PI)
			angle -= 2 * PI;
	}

	//Get the angle (in radian)
	float get() const { return angle; }

	//Get the angle in degree
	float toDegree() const { return 180 * angle / PI; }

	//Hard set the angle
	void set(Angle newAngle) {
		this->angle = newAngle.get();
		if (newAngle.get() < 0 || newAngle.get() > 2 * PI)
			add(0);
	}

	//Difference between another angle and this one, result in [-PI;PI]
	float difference(const Angle other) const {
		float angleDifference = other.get() - angle;
		if (angleDifference < -PI)//Make 4 cases 2
			angleDifference += 2 * PI;
		else if (angleDifference > PI)
			angleDifference -= 2 * PI;

		return angleDifference;
	}

	//Rotate at a certain speed toward a certain angle
	bool rotate(Angle directionAngle, float rotatingSpeed, float deltaTime) {
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

	//Operator == override
	bool operator==(const Angle other) const {
		return angle == other.get();
	}

	//Operator != override
	bool operator!=(const Angle other) const {
		return angle != other.get();
	}
};

