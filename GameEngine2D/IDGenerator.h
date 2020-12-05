#pragma once
#include <vector>

namespace ge {
	/*
	 * IDGenerator give you an valid and unique ID, and allow you to delete an existing ID
	*/
	template <typename T = uint32_t>
	class IDGenerator {
	private:
		std::vector<T> deletedID;
		T maxUsedID{ 0 };
	public:
		//Get a ID that is valid and not used
		T getNewID();

		//Add an ID into the list of used ID. Return true if the id did not exist (and the add was successful)
		bool addID(T id);

		//Delete an id, return true if the id has been deleted
		bool deleteID(T id);
	};

	template <typename T>
	T IDGenerator<T>::getNewID() {
		if (deletedID.empty()) {
			maxUsedID++;
			return maxUsedID - 1;
		}
		else {
			T id = deletedID.back();
			deletedID.pop_back();
			return id;
		}
	}

	template <typename T>
	bool IDGenerator<T>::addID(T id) {
		//If the new id is greater than the greater last id
		if (id > maxUsedID) {
			//Store every non used id
			for (T i = maxUsedID + 1; i < id; i++) {
				deletedID.push_back(i);
			}
			maxUsedID = id;
			return true;
		}
		else {
			//Else check in the deleted id if it is there
			for (T delID : deletedID) {
				if (delID == id) {
					deletedID.erase(delID);
					return true;
				}
			}
			//If it is not found in the deletedID, the id is already used
			return false;
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
