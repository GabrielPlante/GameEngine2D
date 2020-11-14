#pragma once

#include "Entity.h"

namespace ge {
	class Script {
	private:
		friend class ScriptSystem;
	protected:
		Entity entity{ 0 };
	public:
		//onCreate is called when the component is created
		virtual void onCreate() {}

		//onUpdate is called each frame
		virtual void onUpdate() {}

		//onDestroy is called when the component is destroyed
		virtual void onDestroy() {};
	};
}
