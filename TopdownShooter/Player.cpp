#define _USE_MATH_DEFINES
#include <cmath>

#include "Level1.h"

#include "Player.h"
#include "Bullet.h"

Player::Player(sf::Texture& texture)
	: GameObject(texture)
{
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Player::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.move(-300 * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.move(300 * deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sprite.move(0, -300 * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sprite.move(0, 300 * deltaTime);


	sf::Vector2f lookDir = sf::Vector2f(Game::getMousePosition()) - sprite.getPosition();
	sprite.setRotation(std::atan2f(lookDir.y, lookDir.x) * 180.0f / float(M_PI));

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		Game::attachLevel(new Level1());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		Game::addGameObject(new Bullet(Game::getTexture("bullet")))->setPosition(sprite.getPosition());
	}
}
