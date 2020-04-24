# GameEngine2D
GameEngine2D use the Entity - Component - System architecture.

This architecture allow for a much simpler design than OOP and a huge performance improvement due to less cache miss (this come very handy when doing machine learning) at the cost of a more tricky implementation.


## How the ECS architecture work:
A component is a simple bag of data, and is stored in a factory contiguously.

Entity have a list of component, and systems operate on those component.

In a simple OOP design, each frame the system update every entity that contain their own data and are all over the memory, whilst in the ECS design each system iterate over it's component factory thus produce less cache miss.


## How the engine work and how to use it

### The singletons:
The engine let you access those singletons from anywhere:

* The engine
* The console
* The command list

### System and component:
The engine manage every system.

To implement a system, create it and make it inherit the System class, then add it to the engine.

You have the responsability to store the components. For this, the engine provide a very useful Factory class.

Following the ECS design, your system should use his update function to iterate over one or more factory and update each one of it's component.

### Factory:
You should create one factory per different component.

A factory store every component contiguously, that mean that you cannot use polymorphism on component (but you shouldn't do it in the first place).

When your factory is created, you can give it a component, it will give you back an id that you can use later to get the component.

### Messaging system:
A standard messaging system with the subscriber/publisher pattern is available

### Event system:
The base event system is the console event system.
You need to create your own handler inheriting from EventHandler.

The engine hold a pile of event handler, push your event handler on the pile and it will be used.


### Graphic system:
You also need to create a graphic system inheriting from system and give it to the engine by the method addGraphicSystem.
You can change the font by replacing the "mainFont.ttf" file.

### Command:
To implement a command, create a class that inherit from Command, call the constructor of Command with the name of your command, and add your command to the commandList singleton with the method addCommand.

The unimplemented command "quitconsole" is called each time the escape button is pressed while in the console.
