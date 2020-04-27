#include "Drawer.h"

namespace ge {
	SDL_Renderer* Drawer::renderer = nullptr;

	void Drawer::addRenderer(SDL_Renderer* newRenderer) { Drawer::renderer = newRenderer; }

	SDL_Renderer* Drawer::startDrawing(Vector2<int> size, Color color, Uint32 format) {
		//Create the texture with the right parameter
		texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, size.x, size.y);
		//Set the right color
		SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(color.red), static_cast<Uint8>(color.green), static_cast<Uint8>(color.blue), static_cast<Uint8>(color.alpha));
		//Now every drawing will affect the texture not the global renderer
		SDL_SetRenderTarget(renderer, texture);
		return renderer;
	}

	TextureWrapper Drawer::finishDrawing(bool blend) {
		//Now every drawing will affect the global renderer not the texture
		SDL_SetRenderTarget(renderer, NULL);
		if (blend)
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		TextureWrapper textureWrap{ texture };
		texture = nullptr;
		return textureWrap;
	}
}