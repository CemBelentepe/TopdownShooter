#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	float speed;
public:
	Bullet(sf::Texture& texture)
		: GameObject(texture), speed(800)
	{}

	void update(float deltaTime) override;
};

