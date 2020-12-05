#include "Level1.h"
#include "Player.h"
#include "Tilemap.h"

#include <iostream>

Level1::Level1()
{
	resources["player"].loadFromFile("res/player.png");
	resources["bullet"].loadFromFile("res/bullet.png");

	resources["tile1"].loadFromFile("res/tile1.png");
	resources["tile2"].loadFromFile("res/tile2.png");
	resources["tile3"].loadFromFile("res/tile3.png");

	std::vector<TileInfo> tileset{ TileInfo(resources["tile1"]), TileInfo(resources["tile2"], true), TileInfo(resources["tile3"], true) };

	std::vector<std::vector<size_t>> map{
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0} };

	TileObject* tilemap = new TileObject(tileset, map);
	gameObjects.push_back(tilemap);
	gameObjects.push_back(new Player(resources["player"], tilemap));
}

Level1::~Level1()
{
	std::cout << "Level1 destroyed" << std::endl;
}
