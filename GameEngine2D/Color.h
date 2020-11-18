#pragma once

namespace ge {
	struct Color {
		//The color composant
		unsigned char red{ 0 };
		unsigned char green{ 0 };
		unsigned char blue{ 0 };
		unsigned char alpha{ 0 };

		//Default constructor
		Color() {}

		//Constructor with the color
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
			:red{ r }, green{ g }, blue{ b }, alpha{ a }
		{}
	};
}
