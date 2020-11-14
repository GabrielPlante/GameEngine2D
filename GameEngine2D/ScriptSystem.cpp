#include "ScriptSystem.h"

#include "ScriptComponent.h"
#include "Storage.h"
#include "Script.h"

namespace ge {
	void ScriptSystem::update() {
		for (auto it = Storage<ScriptComponent>::begin(); it != Storage<ScriptComponent>::end(); it++) {
			//If the component is not initialised but binded to a script, initialise it
			if (!it->isInitialised && it->script) {
				it->isInitialised = true;
				it->script->entity = it.id();
				it->script->onCreate();
			}
			//If the component is binded to a script, update the script
			if (it->script)
				it->script->onUpdate();
		}
	}
}
