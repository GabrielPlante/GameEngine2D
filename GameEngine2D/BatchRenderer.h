#pragma once
#include <memory>

namespace ge {
	class Shader;
	class BatchRenderer
	{
	protected:
		std::shared_ptr<Shader> shader;

		//Constructor protected so outside class can't construct a batch renderer as it is not mean't to be instanciated
		BatchRenderer(std::shared_ptr<Shader>&& shader) : shader{ std::move(shader) } {}

		uint32_t IBID;
		int lastIndexPlace{ 0 };
	public :
		//Render this batch
		void renderBatch() const;
	};
}
