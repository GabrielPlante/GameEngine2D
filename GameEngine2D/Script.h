#pragma once
#include <string>

#include "Entity.h"

namespace ge {
	//The base class for scripts.
	//You can override the onCreate, onUpdate, and onDestroy method to add behaviour with this script.
	//Once created, you need to bind your subclass to a ScriptComponent of your entity.
	//A Script need a default constructor
	class Script {
	private:
		friend class ScriptSystem;

		std::string name;
	protected:
		Entity entity{ 0 };
	public:
		//Constructor, take the name of the script
		Script(const std::string& name) : name{ name } {}

		//Get the name of this script
		const std::string& getName() const { return name; }

		//onCreate is called when the component is created
		virtual void onCreate() {}

		//onUpdate is called each frame
		virtual void onUpdate() {}

		//onDestroy is called when the component is destroyed
		virtual void onDestroy() {};
	};
}
