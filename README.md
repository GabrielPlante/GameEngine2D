# GameEngine2D
GameEngine2D is the game engine used to support the yet to be made Ianagd game. It is mean to be easy to use, flexible, scalable, reliable and fast.

How the engine work:
Everything the game will have is in stored in component, that are stored a factory.

There are some singleton that you can access from everywhere:
-The engine
-The console
-The event console
-The command list

To create system and component you need to:
-Create one or multiple component class that is a bag of data
-Create a system class that inherit from System with a factory of your(s) component
-Add that factory to the game engine

In the update method of your system you can update every component of the system.

How the factory work:
You give it a component, it will add it to it's system, and give you an id back.
This id can give you access your component at any moment.

A standard messaging system with the subscriber/publisher pattern is available

How the event system work:
The engine start with the console and the console event handler on the foreground.
You need to create your own handler inheriting from EventHandler and make the event system switch to your system.
The unimplemented command "quitconsole" is called each time the escape button is pressed while in the console.
