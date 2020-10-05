#include "TextureWrapper.h"

namespace ge {
	IDGenerator<> TextureWrapper::idGenerator{};
	std::map<unsigned int, int> TextureWrapper::instanceCounter{};

	void TextureWrapper::clean() {
		if (texture != nullptr) {
			instanceCounter.find(id)->second--;
			//If no more instance of this texture exist, delete it
			if (instanceCounter.find(id)->second == 0) {
				SDL_DestroyTexture(texture);
				instanceCounter.erase(id);
				idGenerator.deleteID(id);
			}
		}
	}

	TextureWrapper::TextureWrapper(SDL_Texture* texture) : texture{ texture } {
		if (texture != nullptr) {
			id = idGenerator.getNewID();
			//This is the first wrapper for this texture, create a new instance
			instanceCounter.insert(std::pair<unsigned int, int>(id, 1));
		}
	}

	TextureWrapper::TextureWrapper(const TextureWrapper& other) : texture{ other.get() }, id{ other.getId() } {
		//If the texture given is not null, then we take into account the fact that it was duplicated
		if (other.get() != nullptr)
			instanceCounter.find(id)->second++;
	}

	TextureWrapper& TextureWrapper::operator=(const TextureWrapper& other) {
		//Avoid self assignement
		if (this == &other)
			return *this;
		//Clean
		clean();
		//Get the other parameter
		id = other.getId();
		texture = other.get();
		if (texture != nullptr)
			instanceCounter.find(id)->second++;

		return *this;
	}

	TextureWrapper& TextureWrapper::operator=(SDL_Texture* newTexture) {
		clean();
		texture = newTexture;
		if (newTexture != nullptr) {
			id = idGenerator.getNewID();
			instanceCounter.insert(std::pair<unsigned int, int>(id, 1));
		}
		return *this;
	}

	SDL_Rect TextureWrapper::getTextureRect() const {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		return rect;
	}

	void TextureWrapper::render(SDL_Renderer* renderer, ge::Vector2<int> position, SDL_Rect* srcRect, SDL_Rect* dstRect) const {
		//If no destination rectangle is provided, build it ourself
		if (!dstRect) {
			SDL_Rect rect{ getTextureRect() };
			rect.x = position.x;
			rect.y = position.y;
			SDL_RenderCopy(renderer, texture, srcRect, &rect);
		}
		else
			SDL_RenderCopy(renderer, texture, srcRect, dstRect);
	}
}
