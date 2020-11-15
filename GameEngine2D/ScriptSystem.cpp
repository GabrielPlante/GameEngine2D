#include "ScriptSystem.h"

#include "ScriptComponent.h"
#include "Storage.h"
#include "Script.h"

namespace ge {
	void ScriptSystem::update() {
		for (auto it = Storage<ScriptComponent>::begin(); it != Storage<ScriptComponent>::end(); it++) {
			//Initialise the non initialised script
			while (it->uninitialisedScript.size() > 0) {
				//Create the last script of the list
				Script* script{ it->scripts[it->uninitialisedScript.back()] };
				script->entity = it.id();
				script->onCreate();
				//Remove it from the uninitialised scripts
				it->uninitialisedScript.pop_back();
			}
			//If the component is binded to a script, update the script
			for (Script* script : it->scripts)
				script->onUpdate();
		}
	}
}
