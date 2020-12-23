#pragma once

namespace ge {
	struct Color {
		//The color composant
		float red{ 0 };
		float green{ 0 };
		float blue{ 0 };
		float alpha{ 0 };

		//Default constructor
		Color() {}

		//Constructor with the color
		Color(float r, float g, float b, float a = 255)
			:red{ r }, green{ g }, blue{ b }, alpha{ a }
		{}
	};
}
