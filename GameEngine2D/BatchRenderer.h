#pragma once
#include <stdint.h>//uint32_t

namespace ge {
	class BatchRenderer
	{
	protected:
		//Constructor protected so outside class can't construct a batch renderer as it is not mean't to be instanciated
		BatchRenderer() {}

		uint32_t IBID;
		int lastIndexPlace{ 0 };
	public :
		//Render this batch
		void renderBatch() const;
	};
}
