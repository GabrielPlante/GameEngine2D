#include "Font.h"
#include <stdexcept>

#include <iostream>


namespace ge {
	Font::Font(int fontSize, const std::string& fontFileName)
	{
		font = TTF_OpenFont(fontFileName.c_str(), static_cast<int>(fontSize));
		if (!font)
			throw std::runtime_error("Could not open the font " + fontFileName + "; " + SDL_GetError());
	}

	int Font::getWidth(const std::string& text) const {
		int width;
		TTF_SizeText(font, text.c_str(), &width, nullptr);
		return width;
	}

	int Font::getHeight() const {
		return TTF_FontHeight(font);
	}

	Font::~Font()
	{
		TTF_CloseFont(font);
	}
}
