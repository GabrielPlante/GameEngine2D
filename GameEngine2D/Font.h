#pragma once
#include <SDL_ttf.h>
#include <string>
class Font
{
private:
	//No copy constructor, because the font keep the actual font open
	Font(const Font&) {}

	TTF_Font* font{ nullptr };
public:
	//Constructor, fontFileName is by default mainFont.ttf
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
