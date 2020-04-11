#pragma once
#include "Renderable.h"
#include "Color.h"

namespace ge {
	/*
	 *The graphic representation of a rectangle
	 *The position of the rectanle is the position of the left upper corner
	*/
	class RenderableRectangle :
		public Renderable
	{
	private:
		//The width and height of the rectangle
		int w;
		int h;

		//The color of the rectangle
		Color color;
	public:
		//Constructor
		RenderableRectangle(int w, int h, Color color);

		//Render the rectangle
		void render(SDL_Renderer* renderer, const Camera& camera, const Vector2<>& position) const override;

		//Render the rectangle in a position relative to the window
		void renderWithoutCamera(SDL_Renderer* renderer, const Vector2<>& position, SDL_Rect* dstRect = nullptr) const;

		//Get the color of the rectangle
		const Color& getColor() const { return color; }

		//Change the color of the rectangle
		void changeColor(Color newColor) { color = newColor; }

		//Get the widht of the rectangle
		int getW() const { return w; }

		//Get the height of the rectangle
		int getH() const { return h; }
	};

}
