#include "IDGenerator.h"

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
