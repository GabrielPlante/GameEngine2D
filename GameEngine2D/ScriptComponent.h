#pragma once
#include <vector>

#include "Script.h"

namespace ge {
	//This component is holding every script of an entity.
	//To add a script to an entity, you must first add a ScriptComponent to this entity, then add script to this component.
	struct ScriptComponent {
	private:
		friend class ScriptSystem;

		//The list of script not initialised
		std::vector<size_t> uninitialisedScript;

		//The pointer to the script
		std::vector<Script*> scripts;
	public:
		//Bind a script to this component
		template <typename T>
		void bindScript() { uninitialisedScript.push_back(scripts.size()); scripts.push_back(new T); }

		//Delete a script with his name. Return true if the script is deleted.
		//Deleting a script not initialised will result in undefined behaviour.
		bool deleteScript(const std::string& name);

		//RAII
		~ScriptComponent();
	};
}
