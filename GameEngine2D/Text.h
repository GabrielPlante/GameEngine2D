#pragma once
#include <string>
#include <SDL.h>
#include "Font.h"
#include "Color.h"
#include "Rectangle.h"
class Text
{
public:
	Text(const std::string& text, const Position<>& position, SDL_Renderer* renderer, const Font& font, const Color& color = Color{ 255, 255, 255 });
	void render(SDL_Renderer* renderer, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr) const;
	const Rectangle& getRect() const { return rect; }
	Text(Text&& text) = default;
	~Text();
private:
	Text(const Text&) {}
	Color color;
	Rectangle rect;
	SDL_Texture* texture = nullptr;
};

