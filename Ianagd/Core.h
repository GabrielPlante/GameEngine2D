#pragma once

struct SDL_Renderer;
namespace ian {
	class Core
	{
	private:
		static Core* instance;

		//Constructor private for singleton
		Core();

		//Default constructor
		~Core();

		//The global renderer
		SDL_Renderer* gRenderer;

	public:
		//Init the singleton
		static void init();

		//Quit the singleton
		static void quit();

		//Get the core instance
		static Core* getInstance() { return instance; }

		//Run the core
		void run();

		//Get the global renderer of the map
		SDL_Renderer* getRenderer() const { return gRenderer; }
	};
}
