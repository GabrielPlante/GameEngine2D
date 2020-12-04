#pragma once
#include <vector>
#include <GL/glew.h>

#include "IDGenerator.h"
#include "Vertex.h"

namespace ge {
	//Class that allow to store all data used to render
	//Buffersize is in vertex
	template <int bufferSize>
	class GLBuffer
	{
	private:
		uint32_t bufferId;

		//The array that contain the vertecices
		Vertex[bufferSize] vertecices;
	public:
		GLBuffer();


	};

	template <int bufferSize>
	GLBuffer<bufferSize>::GLBuffer() {
		//Create the openGL buffer
		glGenBuffers(1, &bufferId);

		//Set the type of buffer
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);

		//Allocate the data
		glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(float), buffer, GL_DYNAMIC_DRAW);
	}
}
