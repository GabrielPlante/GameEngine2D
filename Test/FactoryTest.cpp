#include "pch.h"

//#include "MapTest.h"

#include <string>

#include "../GameEngine2D/Entity.h"
#undef main

TEST(FactoryTest, All) {
	ge::Entity id1{ ge::Entity::Create() };
	ge::Storage<std::string> factory;
	id1.addComponent(std::string("id1"));
	EXPECT_EQ(id1.getComponent<std::string>(), "id1");

	ge::Entity id2{ ge::Entity::Create() };
	ge::Entity id3{ ge::Entity::Create() };
	id2.addComponent(std::string("id2"));
	id3.addComponent(std::string("id3"));
	EXPECT_EQ(id2.getComponent<std::string>(), "id2");
	EXPECT_EQ(id3.getComponent<std::string>(), "id3");

	id2.deleteComponent<std::string>();
	EXPECT_EQ(id3.getComponent<std::string>(), "id3");

	auto it = factory.begin();
	EXPECT_EQ(*it, "id1");
	it++;
	EXPECT_EQ(*it, "id3");
}