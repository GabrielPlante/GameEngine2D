#pragma once
#include <vector>

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
