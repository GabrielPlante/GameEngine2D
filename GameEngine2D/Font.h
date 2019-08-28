#pragma once
#include <SDL_ttf.h>
#include <string>
class Font
{
private:
	//No copy constructor
	Font(const Font&) {}

	TTF_Font* font;
public:
	//Constructor
	Font(int fontSize, const std::string& fontFileName = "mainFont.ttf");

	//Get the font pointer
	TTF_Font* getFont() const { return font; }

	//Get the width of a text in this font
	int getWidth(const std::string& text) const;

	//Get the height of the font (is independant of text)
	int getHeight() const;

	//Destructor
	~Font();
};
