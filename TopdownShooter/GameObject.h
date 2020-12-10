#pragma once
#include "Game.h"

class GameObject
{
public:
	int tag;

public:
	GameObject(int tag = 0)
		: tag(tag)	{ }

	virtual void update(float deltaTime) {}
	virtual void render(sf::RenderWindow& window, float deltaTime) {};

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
	SpriteObject(sf::Texture& texture, int tag = 0)
		: GameObject(tag), sprite(texture)
	{ }

	void render(sf::RenderWindow& window, float deltaTime) override
	{
		window.draw(sprite);
	}
};
