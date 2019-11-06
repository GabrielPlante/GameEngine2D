#pragma once
#include <vector>

namespace ge {
	/*
	 * IDGenerator give you an valid and unique ID, and allow you to delete an existing ID
	*/
	template <typename T = unsigned int>
	class IDGenerator {
	private:
		std::vector<T> deletedID;
		T maxUsedID{ 0 };
	public:
		//Get a ID that is valid and not used
		T getNewID();

		//Delete an id, return true if the id has been deleted
		bool deleteID(T id);
	};

	template <typename T>
	T IDGenerator<T>::getNewID() {
		if (deletedID.empty()) {
			maxUsedID++;
			return maxUsedID;
		}
		else {
			T id = deletedID.back();
			deletedID.pop_back();
			return id;
		}
	}

	template <typename T>
	bool IDGenerator<T>::deleteID(T id) {
		//Check to see if the id is valid
		if (id > maxUsedID)
			return false;
		//Check to see if it is not already deleted
		for (T deletedId : deletedID) {
			if (deletedId == id) {
				return false;
			}
		}
		//Add it to the list
		deletedID.push_back(id);
		return true;
	}

}
