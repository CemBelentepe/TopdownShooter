#pragma once
#include "GameObject.h"

class TileObject;
class Bullet : public SpriteObject
{
private:
	float speed;
	TileObject* tilemap;
public:
	Bullet(sf::Texture& texture, TileObject* tilemap);

	void update(float deltaTime) override;
	bool isAlive() override;
};
