#pragma once
#include <SDL.h>
#include <map>

#include "IDGenerator.h"
#include "Vector2.h"

namespace ge {
	class TextureWrapper
	{
	private:
		static IDGenerator<> idGenerator;

		//Counter of how many duplica there is per instance
		static std::map<unsigned int, int> instanceCounter;

		unsigned int id{ 0 };

		//The actual texture
		SDL_Texture* texture{ nullptr };

		//Cleaning function
		void clean();

	public:
		//For testing purpose
		static const std::map<unsigned int, int>& getInstanceCounter() { return instanceCounter; }

		//Default constructor
		TextureWrapper() {}

		//Constructor with a texture
		TextureWrapper(SDL_Texture* texture);

		//Copy constructor
		TextureWrapper(const TextureWrapper& other);

		//Copy assignement operator
		TextureWrapper& operator=(const TextureWrapper& other);

		//Operator = to assign a texture directly
		TextureWrapper& operator=(SDL_Texture* newTexture);

		//Get a pointer to the texture. /!\ the pointer must not be stored
		SDL_Texture* get() const { return texture; }

		//Get a SDL_Rect the size of the texture
		SDL_Rect getTextureRect() const;

		//Get the id of this texture wrapper
		unsigned int getId() const { return id; }

		//Render the texture at a position
		void render(SDL_Renderer* renderer, ge::Vector2<int> position = { 0, 0 }, SDL_Rect* srcRect = NULL, SDL_Rect* dstRect = NULL) const;

		//Destructor
		~TextureWrapper() {
			clean();
		}
	};
}
