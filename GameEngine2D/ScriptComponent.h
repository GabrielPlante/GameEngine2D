#pragma once
#include "Script.h"

namespace ge {
	struct ScriptComponent {
	private:
		friend class ScriptSystem;

		//Is there a better way ?
		bool isInitialised{ false };

		//The pointer to the script
		Script* script;
	public:
		//Bind a script to this component
		template <typename T>
		void bindScript() { script = new T; }

		//RAII
		~ScriptComponent() {
			if (script) {
				script->onDestroy();
				delete script;
			}
		}
	};
}
