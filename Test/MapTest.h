#include "pch.h"

//#include "../Ianagd/Map.h"

/*
TEST(MapTest, absoluteToRelative) {
	ian::Map map;
	EXPECT_EQ(1, map.absoluteToRelative({ 55, 0 }).x);
	EXPECT_EQ(0, map.absoluteToRelative({ 15, 0 }).x);
	EXPECT_EQ(-1, map.absoluteToRelative({ -15, 0 }).x);
	EXPECT_EQ(-1, map.absoluteToRelative({ -50, 0 }).x);
	EXPECT_EQ(-2, map.absoluteToRelative({ -55, 0 }).x);
	EXPECT_EQ(0, map.absoluteToRelative({ 0, 0 }).x);

	EXPECT_EQ(1, map.absoluteToRelative({ 0, 55 }).y);
	EXPECT_EQ(0, map.absoluteToRelative({ 0, 15 }).y);
	EXPECT_EQ(-1, map.absoluteToRelative({ 0, -15 }).y);
	EXPECT_EQ(-2, map.absoluteToRelative({ 0, -55 }).y);
	EXPECT_EQ(0, map.absoluteToRelative({ 0, 0 }).y);
}

TEST(MapTest, relativeToAbsolute) {
	ian::Map map;
	EXPECT_EQ(50, map.relativeToAbsolute({ 1, 0 }).x);
	EXPECT_EQ(0, map.relativeToAbsolute({ 0, 0 }).x);
	EXPECT_EQ(-50, map.relativeToAbsolute({ -1, 0 }).x);
	EXPECT_EQ(-100, map.relativeToAbsolute({ -2, 0 }).x);
	EXPECT_EQ(100, map.relativeToAbsolute({ 2, 0 }).x);

	EXPECT_EQ(50, map.relativeToAbsolute({ 0, 1 }).y);
	EXPECT_EQ(0, map.relativeToAbsolute({ 0, 0 }).y);
	EXPECT_EQ(-50, map.relativeToAbsolute({ 0, -1 }).y);
	EXPECT_EQ(-100, map.relativeToAbsolute({ 0, -2 }).y);
	EXPECT_EQ(100, map.relativeToAbsolute({ 0, 2 }).y);
}

TEST(MapTest, tileExist) {
	ian::Map map;

	map.addTile({ 0, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ 0, 0 }));

	map.addTile({ 1, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ 1, 0 }));

	map.addTile({ -1, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ -1, 0 }));
	map.addTile({ -2, 0 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ -2, 0 }));

	map.addTile({ 0, -1 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ 0, -1 }));

	map.addTile({ -1, -1 }, ian::TileComponent{});
	EXPECT_TRUE(map.tileExist({ -1, -1 }));

	EXPECT_TRUE(!map.tileExist({ 1, 1 }));
}

TEST(MapTest, absoluteRelative) {
	ian::Map map;
	for (int i = -10; i != 10; i++) {
		for (int j = -10; j != 10; j++) {
			ge::Vector2<int> pos{ i, j };
			EXPECT_EQ(pos, map.absoluteToRelative(map.relativeToAbsolute(pos)));
		}
	}
}*/