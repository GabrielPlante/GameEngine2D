#include "pch.h"

#include "MapTest.h"

#include <string>

#include "../GameEngine2D/Entity.h"

TEST(FactoryTest, All) {
	unsigned int id1{ ge::Entity::Create() };
	ge::Entity& ent1{ ge::Storage<ge::Entity>::get(id1) };
	ge::Storage<std::string> factory;
	ent1.addComponent(std::string("id1"));
	EXPECT_EQ(factory.get(id1), "id1");

	unsigned int id2{ ge::Entity::Create() };
	unsigned int id3{ ge::Entity::Create() };
	ge::Entity& ent2{ ge::Storage<ge::Entity>::get(id2) };
	ge::Entity& ent3{ ge::Storage<ge::Entity>::get(id3) };
	ge::Storage<ge::Entity>::get(id2).addComponent(std::string("id2"));
	ent3.addComponent(std::string("id3"));
	EXPECT_EQ(factory.get(id2), "id2");
	EXPECT_EQ(factory.get(id3), "id3");

	factory.deleteComponent(id2);
	EXPECT_EQ(factory.get(id3), "id3");

	auto it = factory.begin();
	EXPECT_EQ(*it, "id1");
	it++;
	EXPECT_EQ(*it, "id2");
}