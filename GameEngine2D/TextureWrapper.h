#pragma once
#include <SDL.h>
#include <map>

#include "IDGenerator.h"

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
		void clean() {
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

	public:
		//Default constructor
		TextureWrapper() {}

		//Constructor with a texture
		TextureWrapper(SDL_Texture* texture) : texture{ texture } {
			if (texture != nullptr) {
				id = idGenerator.getNewID();
				//This is the first wrapper for this texture, create a new instance
				instanceCounter.insert(std::pair<unsigned int, int>(id, 1));
			}
		}

		//Copy constructor
		TextureWrapper(const TextureWrapper& other) : texture{ other.get() }, id{ other.getId() } {
			//If the texture given is not null, then we take into account the fact that it was duplicated
			if (other.get() != nullptr)
				instanceCounter.find(id)->second++;
		}

		//Copy assignement operator
		TextureWrapper& operator=(const TextureWrapper& other) {
			//Avoid self assignement
			if (this == &other)
				return *this;
			//Clean
			clean();
			//Get the other parameter
			id = other.getId();
			texture = other.get();
			instanceCounter.find(id)->second++;

			return *this;
		}

		//Get a pointer to the texture. /!\ the pointer must not be stored
		SDL_Texture* get() const { return texture; }

		//Get the id of this texture wrapper
		unsigned int getId() const { return id; }

		//Destructor
		~TextureWrapper() {
			clean();
		}
	};
}
