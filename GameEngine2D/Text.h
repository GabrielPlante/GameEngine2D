#pragma once
#include <string>
#include <SDL.h>
#include "Font.h"
#include "Color.h"
#include "Rectangle.h"

namespace ge {
	class Text
	{
	private:
		//No copy constructor because the text keep a surface
		Text(const Text&) {}
		//Color of the text
		Color color;
		//Rectangle representing the text
		Rectangle rect;
		//The actual texture
		SDL_Texture* texture = nullptr;
	public:
		//Constructor
		Text(const std::string& text, const Vector2<>& position, SDL_Renderer* renderer, const Font& font, const Color& color = Color{ 255, 255, 255 });

		//Render the text, with maybe a source rectangle and a destination rectangle
		void render(SDL_Renderer* renderer, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr) const;

		//Get the rectangle of the text
		const Rectangle& getRect() const { return rect; }

		//Move constructor possible
		Text(Text&& text) = default;

		//Destructor
		~Text();
	};

}
