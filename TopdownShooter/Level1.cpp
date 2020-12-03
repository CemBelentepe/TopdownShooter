#include "Level1.h"
#include "Player.h"

#include <iostream>

Level1::Level1()
{
	resources["player"].loadFromFile("res/player.png");
	resources["bullet"].loadFromFile("res/bullet.png");
	gameObjects.push_back(new Player(resources["player"]));
}

Level1::~Level1()
{
	std::cout << "Level1 destroyed" << std::endl;
}
