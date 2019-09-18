#include "pch.h"

#include "../GameEngine2D/IDGenerator.h"



TEST(IDGeneratorTest, All) {
	IDGenerator<int> iDGenerator;
	int id1 = iDGenerator.getNewID();
	int id2 = iDGenerator.getNewID();
	EXPECT_EQ(id1 + 1, id2);

	int id3 = iDGenerator.getNewID();
	EXPECT_EQ(id2 + 1, id3);

	iDGenerator.deleteID(id2);
	int id2bis = iDGenerator.getNewID();
	EXPECT_EQ(id2, id2bis);

	iDGenerator.deleteID(id2);
	id2 = iDGenerator.getNewID();
	EXPECT_EQ(id2, id2bis);

	iDGenerator.deleteID(id2);
	iDGenerator.deleteID(id2);
	id2 = iDGenerator.getNewID();
	EXPECT_EQ(id2, id1 + 1);

	iDGenerator.deleteID(id2);
	iDGenerator.deleteID(id2);
	id2 = iDGenerator.getNewID();
	EXPECT_EQ(id2, id1 + 1);
}
