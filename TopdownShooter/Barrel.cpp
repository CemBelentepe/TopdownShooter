#include "Barrel.h"
#include "Tags.h"
#include "Animation.h"
#include "Bullet.h"

Barrel::Barrel(sf::Texture& texture, sf::Vector2f pos)
	: SpriteObject(texture, (int)Tag::Barrel)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(pos);
}

void Barrel::update(float deltaTime)
{
	std::vector<GameObject*> bullets = Game::getGameObjectsWithTags({ (int)(Tag::Player_Bullet), (int)(Tag::Enemy_Bullet) });

	for (auto& go : bullets)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(go);
		if (bullet)
		{
			sf::Vector2u size = sprite.getTexture()->getSize();
			sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin(), sf::Vector2f(size.x, size.y));
			if (collider.contains(bullet->sprite.getPosition()))
			{
				collided = true;
				bullet->health--;

				AnimObject* anim = new AnimObject(Game::getTexture("explosion"), 8, 0.04f);
				anim->sprite.setPosition(sprite.getPosition());
				anim->sprite.setScale(0.5f, 0.5f);
				Game::addGameObject(anim);
			}
		}
	}
}

bool Barrel::isAlive()
{
	return !collided;
}
