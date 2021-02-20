#define _USE_MATH_DEFINES
#include <cmath>

#include "Enemy.h"
#include "Tags.h"
#include "Tilemap.h"
#include "Bullet.h"
#include "Animation.h"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f pos, TileObject* tilemap)
	: SpriteObject(texture, (int)Tag::Enemy), tilemap(tilemap), health(3), cooldown(2)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(pos);
}

void Enemy::update(float deltaTime)
{
	auto moveIfCan = [&](float dx, float dy) {
		sf::Vector2f nextPos = sprite.getPosition() + sf::Vector2f(dx, dy);
		if (!tilemap->canCollide(nextPos))
			sprite.setPosition(nextPos);
	};

	SpriteObject* player = (SpriteObject*)Game::getGameObjectsWithTag((int)Tag::Player)[0];

	sf::Vector2f dist = sf::Vector2f(player->sprite.getPosition() - sprite.getPosition());
	sprite.setRotation(std::atan2f(dist.y, dist.x) * 180.0f / float(M_PI));

	float mag = std::sqrt(dist.x * dist.x + dist.y * dist.y);
	dist /= mag;
	if (mag > 128)
	{
		moveIfCan(dist.x * 128 * deltaTime, 0);
		moveIfCan(0, dist.y * 128 * deltaTime);
	}
	else if (mag < 100)
	{
		moveIfCan(-dist.x * 128 * deltaTime, 0);
		moveIfCan(0, -dist.y * 128 * deltaTime);
	}

	if (cooldown <= 0)
	{
		SpriteObject* bullet = new Bullet(Game::getTexture("bullet"), tilemap, (int)Tag::Enemy_Bullet);
		bullet->sprite.setPosition(sprite.getPosition());
		bullet->sprite.setRotation(sprite.getRotation());
		Game::addGameObject(bullet);
		cooldown = 2;
	}

	cooldown -= deltaTime;

	std::vector<GameObject*> bullets = Game::getGameObjectsWithTag((int)(Tag::Player_Bullet));
	for (auto& go : bullets)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(go);
		if (bullet)
		{
			sf::Vector2u size = sprite.getTexture()->getSize();
			sf::FloatRect collider(sprite.getPosition() - sprite.getOrigin(), sf::Vector2f(size.x, size.y));
			if (collider.contains(bullet->sprite.getPosition()))
			{
				this->health--;
				bullet->health--;

				AnimObject* anim = new AnimObject(Game::getTexture("explosion"), 8, 0.04f);
				anim->sprite.setPosition(sprite.getPosition());
				anim->sprite.setScale(0.25f, 0.25f);
				Game::addGameObject(anim);
			}
		}
	}
}

bool Enemy::isAlive()
{
	return health > 0;
}
