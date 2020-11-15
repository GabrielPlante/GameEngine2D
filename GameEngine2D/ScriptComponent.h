#pragma once
#include <vector>

#include "Script.h"

namespace ge {
	//This component hold script. There is no limit to the number of script this component can hold but it is not possible to remove a script from this component
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

		//RAII
		~ScriptComponent() {
			for (Script* script : scripts){
				script->onDestroy();
				delete script;
			}
		}
	};
}
