#pragma once
#include "GameObject.h"

class TileObject;
class Enemy : public SpriteObject
{
public:
	Enemy(sf::Texture& texture, sf::Vector2f pos, TileObject* tilemap);
	void update(float deltaTime) override;
	bool isAlive() override;

private:
	TileObject* tilemap;
	float cooldown;
	float health;
};