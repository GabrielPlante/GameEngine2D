#pragma once
#include "Text.h"
#include "RenderableRectangle.h"

class TextInRect :
	public Text, public RenderableRectangle
{
private:
	//The position of the upper left corner
	Position<> position;
	int borderSize;
	Color borderColor;
public:
	//Constructor
	TextInRect(RenderableRectangle graphicRect, const std::string& text, SDL_Renderer* renderer,
		Position<> position, Position<> textPosition, const Font& font, Color textColor = Color{ 0, 0, 0 },
		int borderSize = 0, Color borderColor = Color{ 200, 200, 200 });

	//Constructor when the text is centered
	TextInRect(Color backgroundColor, const std::string& text, SDL_Renderer* renderer, Position<> position,const Font& font,
		Color textColor = Color{ 0, 0, 0 }, int borderSize = 0, int textMargin = 0, Color borderColor = Color{ 200, 200, 200 });

	//Render the text and the rectangle
	void render(SDL_Renderer* renderer, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr) const;

	//Get the position of the upper left corner
	const Position<>& getPosition() const { return position; }
};

