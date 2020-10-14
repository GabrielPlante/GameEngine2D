#pragma once
#include <vector>
#include <functional>

#include "Vector2.h"

namespace ge {
	template <typename T>
	class VectorOfVector
	{
		friend class Iterator;
	private:
		//The actual storage of the vector
		std::vector<std::vector<T>> vector;

		std::function<T()> buildDefaultElement;
		std::function<bool(const T&)> isValid;
	public:
		//Constructor
		VectorOfVector(std::function<T()> buildDefaultElement, std::function<bool(const T&)> isValid) : buildDefaultElement{ buildDefaultElement }, isValid{ isValid } {}

		//Add an element at a given position
		void addElement(ge::Vector2<size_t> position, T&& element);

		//Delete an element at a given position
		void deleteElement(ge::Vector2<size_t> position);

		//Check if an element exist
		bool elementExist(ge::Vector2<size_t> position) const { return vector.size() > position.x && vector[position.x].size() > position.y && isValid(vector[position.x][position.y]); }

		//Get the element at the given position. Does not check if the element exist
		T& operator[](ge::Vector2<size_t> position) { return vector[position.x][position.y]; }
		const T& operator[](ge::Vector2<size_t> position) const { return vector[position.x][position.y]; }

		class Iterator {
		private:
			VectorOfVector<T>* vectorOfVector;
			ge::Vector2<size_t> position{ 0, 0 };
			bool hasEnded{ false };
		public:
			//Constructor
			Iterator(VectorOfVector<T>* vectorOfVector, ge::Vector2<size_t> startPosition = { 0, 0 }) : vectorOfVector{ vectorOfVector }, position{ startPosition } {
				if (!vectorOfVector->elementExist(position))
					(*this)++;
			}

			//Increment the iterator to the next tile
			Iterator operator++(int);

			//Has the iterator reached the end
			bool endReached() const { return hasEnded; }

			//Get the element pointed by the vector
			T* operator->() const { return &(*vectorOfVector)[position]; }
			T& operator*() { return (*vectorOfVector)[position]; }

			//Get the actual position of the iterator
			Vector2<size_t> getPosition() const{ return position; }
		};

		//Get the operator at the beggining of the vector of vector
		VectorOfVector<T>::Iterator begin() { return Iterator{ this }; }
	};

	//Implementation here because template cannot be put in cpp file

	template <typename T>
	void VectorOfVector<T>::addElement(ge::Vector2<size_t> position, T&& element) {
		//Make sure the first vector is big enough, fill it with empty vector if needed
		while (vector.size() <= position.x) {
			vector.push_back(std::vector<T>{});
		}
		//Make sure the second vector is big enough, fill it with default element if needed
		while (vector[position.x].size() <= position.y) {
			vector[position.x].push_back(buildDefaultElement());
		}
		//Assign the element to it's place
		vector[position.x][position.y] = element;
	}

	template <typename T>
	void VectorOfVector<T>::deleteElement(ge::Vector2<size_t> position) {
		if (elementExist(position))
			vector[position.x][position.y] = buildDefaultElement();
	}

	template <typename T>
	typename VectorOfVector<T>::Iterator VectorOfVector<T>::Iterator::operator++(int) {
		position.y++;
		//While there are still line to explore in the vector
		while (vectorOfVector->vector.size() > position.x) {
			//While there are still position to explore in the line
			while (vectorOfVector->vector[position.x].size() > position.y) {
				//If the tile exist, we found the next tile
				if (vectorOfVector->elementExist(position))
					return *this;
				position.y++;
			}
			position.x++;
			position.y = 0;
		}
		hasEnded = true;
		return *this;
	}
}

