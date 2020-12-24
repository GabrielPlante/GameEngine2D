#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <array>
#include <GL/glew.h>

#include "BatchRenderer.h"
#include "VertexAttrib.h"
#include "Shader.h"
#include "Entity.h" //No other solution

#ifdef DEBUG_GE
#include <iostream>
#endif // DEBUG_GE


namespace ge {
	//Generic class that allow to store object with the same number of vertex and index and render them all at once
	//The class is created with the static function createBatch
	//The batch is automatically rendered each frame
	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	class Batch
		: public BatchRenderer
	{
	private:
		//The entity containing this batch
		Entity entity;

		uint32_t VAID; //Vertex array id
		uint32_t VBID; //Vertex buffer id
		//uint32_t IBID; //Index buffer id (now defined in the base class BatchRenderer)

		size_t lastObjectPosition{ 0 };
		std::vector<size_t> deletedObjects;

		const size_t objectVertexSize{ sizeof(Vertex) * vertexPerObject };
		const size_t objectIndexSize{ sizeof(uint32_t) * indexPerObject };

		//Private constructor, a batch is made by a static call
		Batch(const std::vector<VertexAttrib>& vertexAttribs, std::shared_ptr<Shader>&& shader, size_t bufferSize);
	public:
		//Create a batch
		//The size bufferSize is in object
		static std::shared_ptr<Batch<Vertex, vertexPerObject, indexPerObject>> createBatch(const std::vector<VertexAttrib>& vertexAttribs, std::shared_ptr<Shader>&& shader, size_t bufferSize);

		//Add objects to the Batch. Return an array filled with the indexes of the objects placed
		std::vector<size_t> addObject(const std::vector<std::array<Vertex, vertexPerObject>>& vertexArrays, const std::vector<std::array<uint32_t, indexPerObject>>& indexArrays);

		//Delete a component
		void deleteObject(size_t objectID);

		//Change the vertexes / indexes of an object
		void changeVertex(size_t objectID, const Vertex* vertexes) const;
		void changeIndex(size_t objectID, const std::array<uint32_t, indexPerObject>& indexes) const;

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

#define BATCH_TEMPLATE Vertex,vertexPerObject,indexPerObject

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	std::shared_ptr<Batch<BATCH_TEMPLATE>> Batch<BATCH_TEMPLATE>::createBatch(const std::vector<VertexAttrib>& vertexAttribs, std::shared_ptr<Shader>&& shader, size_t bufferSize) {
		return std::shared_ptr<Batch<BATCH_TEMPLATE>>{new Batch<Vertex, vertexPerObject, indexPerObject>{ vertexAttribs, std::move(shader), bufferSize }};
	}

	template<typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	Batch<Vertex, vertexPerObject, indexPerObject>::~Batch()
	{
		if (entity.haveComponent<BatchRenderer*>())
			entity.deleteEntity();
	}

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	Batch<BATCH_TEMPLATE>::Batch(const std::vector<VertexAttrib>& vertexAttribs, std::shared_ptr<Shader>&& shader, size_t bufferSize)
		: BatchRenderer{ std::move(shader) }, entity { Entity::Create() }
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

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	//Add objects to the Batch. Return an array filled with the indexes of the objects placed
	std::vector<size_t> Batch<BATCH_TEMPLATE>::addObject
		(const std::vector<std::array<Vertex, vertexPerObject>>& vertexArrays, const std::vector<std::array<uint32_t, indexPerObject>>& indexArrays)
	{
		std::vector<size_t> placedObjectsId{};

		const size_t nbrOfObject{ vertexArrays.size() };
		size_t nbrOfObjectPlaced{ 0 };

		//First fill the deleted position
		while (!deletedObjects.empty() && nbrOfObjectPlaced != nbrOfObject) {
			//Fill the vertex buffer object with the vertexes for one object
			glBindBuffer(GL_ARRAY_BUFFER, VBID);
			glBufferSubData(GL_ARRAY_BUFFER, deletedObjects.back() * objectVertexSize, objectVertexSize, &vertexArrays[nbrOfObjectPlaced]);

			//Change the indexes to the good position
			std::array<uint32_t, indexPerObject> correctIndexes;
			for (size_t i = 0; i != indexPerObject; i++) {
				correctIndexes[i] = static_cast<uint32_t>(indexArrays[nbrOfObjectPlaced][i] + deletedObjects.back() * vertexPerObject);
			}

			//Fill the index buffer object with the indexes for one object
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, deletedObjects.back() * objectIndexSize, objectIndexSize, &correctIndexes[0]);

			placedObjectsId.push_back(deletedObjects.back());

			deletedObjects.pop_back();
			nbrOfObjectPlaced++;
		}

		if (nbrOfObjectPlaced != nbrOfObject) {
			size_t nbrOfObjectRemaining{ nbrOfObject - nbrOfObjectPlaced };
			//Fill the vertex buffer object with the vertexes for the remaining objects
			glBindBuffer(GL_ARRAY_BUFFER, VBID);
			glBufferSubData(GL_ARRAY_BUFFER, lastObjectPosition * objectVertexSize, objectVertexSize * nbrOfObjectRemaining, &vertexArrays[nbrOfObjectPlaced]);

			//Change the indexes to the good position
			std::vector<uint32_t> correctIndexes;
			for (size_t i = 0; i != nbrOfObjectRemaining; i++) {
				for (size_t j = 0; j != indexPerObject; j++) {
					correctIndexes.push_back(static_cast<uint32_t>(indexArrays[nbrOfObjectPlaced + i][j] + (lastObjectPosition + i) * vertexPerObject));
				}
			}

			//Fill the index buffer object with the indexes for the remaining objects
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, lastObjectPosition * objectIndexSize, objectIndexSize * nbrOfObjectRemaining, &correctIndexes[0]);

			for (; nbrOfObjectPlaced != nbrOfObject; nbrOfObjectPlaced++) {
				placedObjectsId.push_back(lastObjectPosition);
				lastObjectPosition++;
			}
		}

		//Update the place of the last index of the base class
		lastIndexPlace = static_cast<int>(lastObjectPosition * indexPerObject);

		return placedObjectsId;
	}

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	void Batch<BATCH_TEMPLATE>::deleteObject(size_t objectID) {
		//If the last object is in the last position
		if (objectID == lastObjectPosition - 1) {
			lastObjectPosition--;
			lastIndexPlace = static_cast<int>(lastObjectPosition * indexPerObject);
		}
		//Else add it to the deleted object
		else {
			deletedObjects.push_back(objectID);
			//And delete it
			//glBindBuffer(GL_ARRAY_BUFFER, VBID);
			//glBufferSubData(GL_ARRAY_BUFFER, objectID * objectVertexSize, objectVertexSize, nullptr);
			std::array<uint32_t, indexPerObject> indexArray;
			indexArray.fill(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, objectID * objectIndexSize, objectIndexSize, &indexArray[0]);
		}
	}

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	void Batch<BATCH_TEMPLATE>::changeVertex(size_t objectID, const Vertex* vertexes) const {
		glBindBuffer(GL_ARRAY_BUFFER, VBID);
		glBufferSubData(GL_ARRAY_BUFFER, objectID * objectVertexSize, objectVertexSize, vertexes);
	}

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	void Batch<BATCH_TEMPLATE>::changeIndex(size_t objectID, const std::array<uint32_t, indexPerObject>& indexes) const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, objectID * objectIndexSize, objectIndexSize, &indexes[0]);
	}

	template <typename Vertex, size_t vertexPerObject, size_t indexPerObject>
	void Batch<BATCH_TEMPLATE>::clear() {
		lastIndexPlace = 0;
		lastObjectPosition = 0;
		deletedObjects.clear();
	}
}

