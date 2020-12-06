#define _USE_MATH_DEFINES
#include <cmath>

#include "Tilemap.h"
#include "Level1.h"

#include "Player.h"
#include "Bullet.h"

Player::Player(sf::Texture& texture, TileObject* tilemap)
	: SpriteObject(texture), cooldown(0.0f), tilemap(tilemap)
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
		SpriteObject* bullet = new Bullet(Game::getTexture("bullet"), tilemap);
		bullet->sprite.setPosition(sprite.getPosition());
		bullet->sprite.setRotation(sprite.getRotation());
		Game::addGameObject(bullet);
		cooldown = 0.25f;
	}

	cooldown -= deltaTime;
}
