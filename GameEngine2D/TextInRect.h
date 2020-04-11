#pragma once
#include "Text.h"
#include "RenderableRectangle.h"

namespace ge {
	class TextInRect :
		public Text, public RenderableRectangle
	{
	private:
		//The position of the upper left corner
		Vector2<> position;
		int borderSize;
		Color borderColor;
	public:
		//Constructor
		TextInRect(RenderableRectangle graphicRect, const std::string& text, SDL_Renderer* renderer,
			Vector2<> position, Vector2<> textPosition, const Font& font, Color textColor = Color{ 0, 0, 0 },
			int borderSize = 0, Color borderColor = Color{ 200, 200, 200 });

		//Constructor when the text is centered
		TextInRect(Color backgroundColor, const std::string& text, SDL_Renderer* renderer, Vector2<> position, const Font& font,
			Color textColor = Color{ 0, 0, 0 }, int borderSize = 0, int textMargin = 0, Color borderColor = Color{ 200, 200, 200 });

		//Render the text and the rectangle
		void render(SDL_Renderer* renderer, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr) const;

		//Get the position of the upper left corner
		const Vector2<>& getPosition() const { return position; }
	};

}
