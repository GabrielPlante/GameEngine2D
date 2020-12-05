#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <memory>
#include <GL/glew.h>

#include "BatchRenderer.h"
#include "Entity.h" //No other solution

namespace ge {
	struct VertexAttrib {
		int size; //In component
		uint32_t type;
		GLboolean normalized{ GL_FALSE };
		const void* pointer;
	};

	//Generic class that allow to store object with the same number of vertex and index and render them all at once
	//The size bufferSize is in object
	//The class is created with the static function createBatch
	//The batch is automatically rendered each frame
	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	class Batch
		: public BatchRenderer
	{
	private:
		//The entity containing this batch
		Entity entity;

		uint32_t VAID; //Vertex array id
		uint32_t VBID; //Vertex buffer id
		//uint32_t IBID; //Index buffer id (now defined in the base class BatchRenderer

		size_t lastObjectPosition{ 0 };
		std::vector<size_t> deletedObjects;

		const size_t objectVertexSize{ sizeof(Vertex) * vertexPerObject };
		const size_t objectIndexSize{ sizeof(uint32_t) * indexPerObject };

		//Private constructor, a batch is made by a static call
		Batch(const std::vector<VertexAttrib>& vertexAttribs);
	public:
		//Create a batch
		static std::unique_ptr<Batch<Vertex, bufferSize, vertexPerObject, indexPerObject>> createBatch(const std::vector<VertexAttrib>& vertexAttribs);

		template <size_t nbrOfObject = 1>
		//Add objects to the Batch. Return an array filled with the indexes of the objects placed
		std::array<size_t, nbrOfObject> addObject(const std::array<Vertex, vertexPerObject* nbrOfObject>& vertexArray, const std::array<uint32_t, indexPerObject* nbrOfObject>& indexArray);

		//Change the vertexes / indexes of an object
		void changeVertex(uint32_t objectID, const Vertex* vertexes) const;
		void changeIndex(uint32_t objectID, const std::array<uint32_t, indexPerObject>& indexes) const;

		void clear();

		//Destructor needed to destroy the component of this batch
		~Batch();
	};


	/*Explanation on the internal function of the class
	* The user create the object with a static method returning a unique_ptr.
	* However a pointer copy of the base class (BatchRenderer) is made to the storage of the ECS system.
	* This allow the graphic system to iterate on those pointer and render the batches,
	* while the user can still do whatever he want with his batch
	* When the instance is deleted, the component is cleared, so there isn't any risk of nullptr exception
	*/

#define BATCH_TEMPLATE Vertex,bufferSize,vertexPerObject,indexPerObject

	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	std::unique_ptr<Batch<BATCH_TEMPLATE>> Batch<BATCH_TEMPLATE>::createBatch(const std::vector<VertexAttrib>& vertexAttribs) {
		return std::unique_ptr<Batch<BATCH_TEMPLATE>>{new Batch<Vertex, bufferSize, vertexPerObject, indexPerObject>{ vertexAttribs }};
	}

	template<typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	Batch<Vertex, bufferSize, vertexPerObject, indexPerObject>::~Batch()
	{
		entity.deleteEntity();
	}

	template <typename Vertex, size_t bufferSize, size_t vertexPerObject, size_t indexPerObject>
	Batch<BATCH_TEMPLATE>::Batch(const std::vector<VertexAttrib>& vertexAttribs)
		: entity{ Entity::Create() }
	{
		//Handle the component storage
		entity.addComponent<BatchRenderer*>(this);

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
	std::array<size_t, nbrOfObject> Batch<BATCH_TEMPLATE>::addObject
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

		//Update the place of the last index of the base class
		lastIndexPlace = static_cast<int>(lastObjectPosition * indexPerObject);

		return placedObjectsId;
	}
}

