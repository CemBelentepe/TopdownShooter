#define _USE_MATH_DEFINES
#include <cmath>

#include "Tilemap.h"
#include "Level1.h"
#include "Animation.h"

#include "Player.h"
#include "Bullet.h"
#include "Tags.h"

Player::Player(sf::Texture& texture, TileObject* tilemap)
	: SpriteObject(texture, (int)Tag::Player), cooldown(0.0f), tilemap(tilemap), health(8)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Player::update(float deltaTime)
{
	auto moveIfCan = [&](float dx, float dy) {
		sf::Vector2f nextPos = sprite.getPosition() + sf::Vector2f(dx, dy);
		if (!tilemap->canCollide(nextPos))
			sprite.setPosition(nextPos);
	};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		moveIfCan(-300 * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		moveIfCan(300 * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		moveIfCan(0, -300 * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		moveIfCan(0, 300 * deltaTime);


	sf::Vector2f lookDir = sf::Vector2f(Game::getMousePosition()) - sprite.getPosition();
	sprite.setRotation(std::atan2f(lookDir.y, lookDir.x) * 180.0f / float(M_PI));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		Game::attachLevel(new Level1());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown <= 0) 
	{
		SpriteObject* bullet = new Bullet(Game::getTexture("bullet"), tilemap, (int)Tag::Player_Bullet);
		bullet->sprite.setPosition(sprite.getPosition());
		bullet->sprite.setRotation(sprite.getRotation());
		Game::addGameObject(bullet);
		cooldown = 0.25f;
	}

	cooldown -= deltaTime;

	std::vector<GameObject*> bullets = Game::getGameObjectsWithTag((int)(Tag::Enemy_Bullet));
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

	if (health < 0)
	{
		// TODO Gameover
	}
}
