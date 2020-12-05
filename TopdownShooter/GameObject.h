#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject()
	{ }

	virtual void update(float deltaTime) {}
	virtual void render(sf::RenderWindow& window) {};

	virtual bool isAlive()
	{
		return true;
	}
};

class SpriteObject : public GameObject
{
public:
	sf::Sprite sprite;

public:
	SpriteObject(sf::Texture& texture)
		: sprite(texture)
	{ }

	void render(sf::RenderWindow& window) override
	{
		window.draw(sprite);
	}
};
