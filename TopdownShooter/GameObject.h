#pragma once
#include "Game.h"

class GameObject
{
protected:
	sf::Sprite sprite;

public:
	GameObject(sf::Texture& texture)
		: sprite(texture) 
	{ }

	virtual void update(float deltaTime) { }
	virtual void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	virtual bool isAlive()
	{
		return true;
	}

	virtual void setPosition(sf::Vector2f pos)
	{
		sprite.setPosition(pos);
	}

	virtual void setRotation(float a)
	{
		sprite.setRotation(a);
	}
};
