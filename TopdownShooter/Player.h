#pragma once
#include "Game.h"
#include "GameObject.h"

class TileObject;
class Player : public SpriteObject
{
private:
	TileObject* tilemap;
	float cooldown;
	int health;

public:
	Player(sf::Texture& texture, TileObject* tilemap);

	void update(float deltaTime) override;
};
