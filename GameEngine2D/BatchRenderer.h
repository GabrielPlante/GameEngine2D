#pragma once

#include "Shader.h"

namespace ge {
	class BatchRenderer
	{
	protected:
		Shader shader;

		//Constructor protected so outside class can't construct a batch renderer as it is not mean't to be instanciated
		BatchRenderer(Shader&& shader) : shader{ std::move(shader) } {}

		uint32_t IBID;
		int lastIndexPlace{ 0 };
	public :
		//Render this batch
		void renderBatch() const;
	};
}
