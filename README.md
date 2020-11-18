# GameEngine2D
GameEngine2D use the Entity - Component - System architecture.

This architecture allow for a much simpler design than OOP and a huge performance improvement due to less cache miss at the cost of a trickier implementation.

GameEngine2D use OpenGL for the graphics part of the engine.

## How the ECS architecture work:
A component is a simple bag of data, and is stored in a factory contiguously.

Contrary to an OOP design, an entity is just a possessor of component. In practice, it is just an id that component know of.

A system operate on one or more types of component to perform the same operation on each.

In a simple OOP design, each frame the system update every entity that contain their own data and are all over the memory, whilst in the ECS design each system iterate over it's component factory thus produce less cache miss.


## How the engine work and how to use it

### The singletons:
The engine let you access those singletons from anywhere:

* The engine
* The command list

### System and component:
The engine manage every system.

To implement a system, create it and make it inherit the System class, then add it to the engine.

The engine provide an entity class where you can create entities and manage their components. The component are stored in the class storage.

Following the ECS design, your system should use his update function to iterate over one or more storage and update each one of it's component.

### Storage:
A storage store every component contiguously, that mean that you cannot use polymorphism on component (but you shouldn't do it in the first place, because a component is just data).

You can access an iterator on the storage but you cannot directly add or remove component from the storage, you have to pass by the entity responsible of the component.

### Messaging system:
A standard messaging system with the subscriber/publisher pattern is available

### Event system:
The base event system is the console event system.
You need to create your own handler inheriting from EventHandler.

The engine hold a pile of event handler, push your event handler on the pile and it will be used.


### Graphic system:
In developpment with OpenGL.

### Command:
To implement a command, create a class that inherit from Command, call the constructor of Command with the name of your command, and add your command to the commandList singleton with the method addCommand.
