#pragma once
#include <cmath>

namespace ge {
	constexpr float PI = 3.14159265f;

	//An angle is a float between 0 and 2*PI
	class Angle
	{
	private:
		//The angle is private because adding angle is non-trivial
		float angle;
	public:
		//Default constructor
		Angle(float angle = 0);

		//Add (or substract) an angle to change the angle
		void add(Angle delta);

		//Get the angle (in radian)
		float get() const { return angle; }

		//Get the angle in degree
		float toDegree() const { return 180 * angle / PI; }

		//Hard set the angle
		void set(Angle newAngle);

		//Difference between another angle and this one, result in [-PI;PI]
		float difference(const Angle other) const;

		//Rotate at a certain speed toward a certain angle
		bool rotate(Angle directionAngle, float rotatingSpeed, float deltaTime);

		//Operator == override
		bool operator==(const Angle other) const { return angle == other.get(); }

		//Operator != override
		bool operator!=(const Angle other) const { return angle != other.get(); }
	};

}
