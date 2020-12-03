#pragma once
#include "Game.h"
#include "GameObject.h"

class Player : public GameObject
{
private:
	float cooldown;
public:
	Player(sf::Texture& texture);

	void update(float deltaTime) override;
};
