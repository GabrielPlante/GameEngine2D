#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <GL/glew.h>

namespace ge {
	struct VertexAttrib {
		int size; //In component
		uint32_t type;
		GLboolean normalized{ GL_FALSE };
		const void* pointer;

	};

	//Generic class that allow to store object with the same number of vertex and index and render them all at once
	//The size bufferSize is in object
	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	class Batch
	{
	private:
		uint32_t VAID; //Vertex array id
		uint32_t VBID; //Vertex buffer id
		uint32_t IBID; //Index buffer id

		size_t lastObjectPosition{ 0 };
		std::vector<size_t> deletedObjects;

		const size_t objectVertexSize{ sizeof(Vertex) * vertexPerObject };
		const size_t objectIndexSize{ sizeof(uint32_t) * indexPerObject };
	public:
		Batch(const std::vector<VertexAttrib>& vertexAttribs);

		template <size_t nbrOfObject = 1>
		//Add objects to the Batch. Return an array filled with the indexes of the objects placed
		std::array<size_t, nbrOfObject> addObject(const std::array<Vertex, vertexPerObject* nbrOfObject>& vertexArray, const std::array<uint32_t, indexPerObject* nbrOfObject>& indexArray);

		//Render the batch
		void renderBatch() const;

		//Change the vertexes / indexes of an object
		void changeVertex(uint32_t objectID, const Vertex* vertexes) const;
		void changeIndex(uint32_t objectID, const std::array<uint32_t, indexPerObject>& indexes) const;

		void clear();
	};



	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	Batch<Vertex, bufferSize, vertexPerObject, indexPerObject>::Batch(const std::vector<VertexAttrib>& vertexAttribs) {
		//Create the vertex array to avoid setting the vertex parameter each frame
		glCreateVertexArrays(1, &VAID);
		glBindVertexArray(VAID);

		//Create the vertex buffer
		glCreateBuffers(1, &VBID);
		glBindBuffer(GL_ARRAY_BUFFER, VBID);
		glBufferData(GL_ARRAY_BUFFER, bufferSize * objectVertexSize, nullptr, GL_DYNAMIC_DRAW);

		//Setup the vertex attributes
		for (int i = 0; i != vertexAttribs.size(); i++) {
			glEnableVertexArrayAttrib(VAID, i);
			glVertexAttribPointer(i, vertexAttribs[i].size, vertexAttribs[i].type, vertexAttribs[i].normalized, sizeof(Vertex), vertexAttribs[i].pointer);
		}

		//Create the index buffer
		glCreateBuffers(1, &IBID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * objectIndexSize, nullptr, GL_DYNAMIC_DRAW);
	}

	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	template <size_t nbrOfObject>
	//Add objects to the Batch. Return an array filled with the indexes of the objects placed
	std::array<size_t, nbrOfObject> Batch<Vertex, bufferSize, vertexPerObject, indexPerObject>::addObject
		(const std::array<Vertex, vertexPerObject* nbrOfObject>& vertexArray, const std::array<uint32_t, indexPerObject* nbrOfObject>& indexArray)
	{
		size_t nbrOfObjectPlaced{ 0 };
		std::array<size_t, nbrOfObject> placedObjectsId{};

		//First fill the deleted position
		while (!deletedObjects.empty() && nbrOfObjectPlaced != nbrOfObject) {
			//Fill the vertex buffer object with the vertexes for one object
			glBindBuffer(GL_ARRAY_BUFFER, VBID);
			glBufferSubData(GL_ARRAY_BUFFER, deletedObjects.back() * vertexPerObject, objectVertexSize, &vertexArray[nbrOfObjectPlaced * vertexPerObject]);

			//Change the indexes to the good position
			std::array<uint32_t, indexPerObject> correctIndexes;
			for (size_t i = 0; i != indexPerObject; i++) {
				correctIndexes[i] = static_cast<uint32_t>(indexArray[nbrOfObjectPlaced * indexPerObject + i] + deletedObjects.back() * indexPerObject);
			}

			//Fill the index buffer object with the indexes for one object
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, deletedObjects.back() * indexPerObject, objectIndexSize, &correctIndexes[0]);

			placedObjectsId[nbrOfObjectPlaced] = deletedObjects.back();

			deletedObjects.pop_back();
			nbrOfObjectPlaced++;
		}

		if (nbrOfObjectPlaced != nbrOfObject) {
			size_t nbrOfObjectRemaining{ nbrOfObject - nbrOfObjectPlaced };
			//Fill the vertex buffer object with the vertexes for the remaining objects
			glBindBuffer(GL_ARRAY_BUFFER, VBID);
			glBufferSubData(GL_ARRAY_BUFFER, lastObjectPosition * vertexPerObject, objectVertexSize * nbrOfObjectRemaining, &vertexArray[nbrOfObjectPlaced * vertexPerObject]);

			//Change the indexes to the good position
			std::vector<uint32_t> correctIndexes;
			for (size_t i = 0; i != indexPerObject * nbrOfObjectRemaining; i++) {
				correctIndexes.push_back(static_cast<uint32_t>(indexArray[nbrOfObjectPlaced * indexPerObject + i] + (lastObjectPosition + i / indexPerObject) * indexPerObject));
			}

			//Fill the index buffer object with the indexes for the remaining objects
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, lastObjectPosition * indexPerObject, objectIndexSize * nbrOfObjectRemaining, &correctIndexes[0]);

			for (; nbrOfObjectPlaced != nbrOfObject; nbrOfObjectPlaced++) {
				placedObjectsId[nbrOfObjectPlaced] = lastObjectPosition;
				lastObjectPosition++;
			}
		}

		return placedObjectsId;
	}

	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	void Batch<Vertex, bufferSize, vertexPerObject, indexPerObject>::renderBatch() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(lastObjectPosition * indexPerObject), GL_UNSIGNED_INT, (void*)0);
	}
}

