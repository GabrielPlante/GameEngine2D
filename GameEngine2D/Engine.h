#pragma once
#include <vector>
#include <memory>

#include "Clock.h"
#include "System.h"
#include "EventSystem.h"
#include "Publisher.h"

namespace ge {
	class GraphicSystem;

	/// <summary>
	/// Engine class, singleton. It is the back bone of the game engine, everything happen here.
	/// <para>The engine initialize the console and the command list</para>
	/// <para>Before calling gameLoop and thus make the engine run, you have to :</para>
	/// <para>- Add an event handler with pushEventHandler, else the console event handler will be used</para>
	/// <para>- Add an graphic system with addGraphicSystem, else the engine will crash</para>
	/// <para>- Add every system you want with addSystem, it will be harder to add them after</para>
	/// <para>Instead of calling gameLoop, you can implement your own loop that call update, but the stop method and the timestep will not work anymore.</para>
	/// <para>It is a publisher, meaning a subscriber can subscribe to him and it can send message to it's subscriber
	/// </summary>
	class Engine
		: public Publisher
	{
	private:
		Clock engineClock;
		long long timeSinceStart{ 0 };
		//Updated at the very begining of each frame, give the time since the begining of the last frame
		long long timeSinceLastFrame{ 0 };

		static Engine* instance;

		//Boolean that dictate if the main loop continue or stop
		bool keepRunning{ true };

		//Time between each frame in milliseconds, with the base being 60 frame per second
		unsigned int timeBetweenFrame{ 1000 / 60 };

		//The vector containing all the systems
		std::vector<std::shared_ptr<System>> systems;

		//The event system
		EventSystem eventSystem;

		//The graphic system have it's own variable to make sure it is updated last
		std::shared_ptr<System> graphicSystem;

		//Reset the engine clock, but keep track of the time since the engine started, and give how much time passed since the last clock reset
		long long timestep();


		/// <summary>
		/// This class is used to initialise and destruct SDL
		/// </summary>
		class SDLInit
		{
		public:
			//Constructor, initialise SDL
			SDLInit();

			//Destructor, stop SDL
			~SDLInit();
		};

		//This will initialise sdl
		SDLInit sdl_init{};

		//Default constructor, private to make it a singleton
		Engine();

		//Default destructor
		~Engine();

	public:
		//Initialize the engine
		static void init();

		//Return a pointer to the engine instance, or nullptr if it's not initialized yet
		static Engine* getInstance() { return instance; }

		//Quit the engine, destroying this instance
		static void quit();

		//The mainLoop, call update each time, and timestep
		void mainLoop();

		//Called each frame
		void update();

		//Add a system to the engine, return it's position
		size_t addSystem(std::shared_ptr<System> system) { systems.push_back(system); return systems.size() - 1; }

		//Get the size of the system stack
		size_t getSystemSize() const { return systems.size(); }

		//Clear every systems except the graphic and the event system
		void clearSystems() { systems.clear(); }

		//Stop the main loop, stopping the engine
		void stop() { keepRunning = false; }

		//Updated at the very begining of each frame, give the time since the begining of the last frame. The time is in microsecond
		long long getTimeSinceLastFrame() const { return timeSinceLastFrame; }

		//Get the time since the engine with initiliased in microsecond
		long long getTimeSinceStart() const { return timeSinceStart + engineClock.getTime(); }

		//Push an event handler that will be used from now on
		void pushEventHandler(std::unique_ptr<EventHandler> eventHandler) { eventSystem.pushEventHandler(std::move(eventHandler)); }

		//Pop the top event, the next one will be used from now on
		void popEventHandler() { eventSystem.popEventHandler(); }

		//Get the size of the event handler pile
		size_t getEventHandlerPileSize() const { return eventSystem.getEventHandlerPileSize(); }

		//Add a graphic system to the engine
		void addGraphicSystem(std::shared_ptr<System> newGraphicSystem) { graphicSystem = std::move(newGraphicSystem); }

		//Get the minimum amount of time that pass between two frame
		unsigned int getTimeBetweenFrame() const { return timeBetweenFrame; }

		//Set the minimum amount of time that pass between two frame
		void setTimeBetweenFrame(unsigned int newTimeBetweenFrame) { timeBetweenFrame = newTimeBetweenFrame; }

		//Set a new time scale. A time scale change the way the time flow. If time scale is 2, the time will pass 2 time faster
		void setTimeScale(double newTimeScale) { engineClock.setTimeScale(newTimeScale); }
	};

}
