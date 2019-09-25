#include "pch.h"

#include <string>

#include "../GameEngine2D/Factory.h"

TEST(FactoryTest, All) {
	ge::Factory<std::string> factory;
	unsigned int id1 = factory.addComponent("id1");
	EXPECT_EQ(*factory.getComponent(id1), "id1");

	unsigned int id2 = factory.addComponent("id2");
	unsigned int id3 = factory.addComponent("id3");
	EXPECT_EQ(*factory.getComponent(id2), "id2");
	EXPECT_EQ(*factory.getComponent(id3), "id3");

	factory.deleteComponent(id2);
	EXPECT_EQ(*factory.getComponent(id3), "id3");

	auto it = factory.getBeginningIterator();
	EXPECT_EQ(*it, "id1");
	it++;
	EXPECT_EQ(*it, "id3");
}