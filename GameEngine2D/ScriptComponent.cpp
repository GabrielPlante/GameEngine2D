#include "ScriptComponent.h"

namespace ge {
	bool ScriptComponent::deleteScript(const std::string& name)
	{
		for (auto it = scripts.begin(); it != scripts.end(); it++) {
			if ((*it)->getName() == name) {
				(*it)->onDestroy();
				delete *it;
				scripts.erase(it);
				return true;
			}
		}
		return false;
	}

	ScriptComponent::~ScriptComponent() {
		for (Script* script : scripts) {
			script->onDestroy();
			delete script;
		}
	}
}