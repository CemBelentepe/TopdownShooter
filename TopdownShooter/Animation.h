#pragma once
#include "GameObject.h"

class AnimObject : public SpriteObject
{
private:
	int current_step;
	float frameTime;
	int frames;
	float animTime;
	sf::IntRect frameRect;
	bool onlyOnce;
public:
	AnimObject(sf::Texture& texture, int frames, float animTime, bool onlyOnce = true)
		: SpriteObject(texture), current_step(0), frameTime(animTime), frames(frames), animTime(animTime), 
		frameRect(sf::Vector2i(0, 0), sf::Vector2i(texture.getSize().x / frames, texture.getSize().y)),
		onlyOnce(onlyOnce)
	{
		sprite.setTextureRect(frameRect);
		sprite.setOrigin(frameRect.width / 2, frameRect.height/ 2);
	}

	void render(sf::RenderWindow& window, float deltaTime) override
	{
		if (frameTime <= 0)
		{
			current_step = (current_step + 1) % (2 * frames);
			frameRect.left = (current_step % frames) * frameRect.width;
			sprite.setTextureRect(frameRect);
			frameTime = animTime;
		}

		window.draw(sprite);

		frameTime-=deltaTime;
	}

	bool isAlive() override
	{
		if (onlyOnce)
			return current_step < frames;
		else
			return true;
	}
};