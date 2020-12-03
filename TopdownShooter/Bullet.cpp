#define _USE_MATH_DEFINES
#include <cmath>

#include "Bullet.h"

void Bullet::update(float deltaTime)
{
	sf::Vector2f dx(std::cos(sprite.getRotation() / 180 * M_PI),std::sin(sprite.getRotation() / 180 * M_PI));
	dx *= speed * deltaTime;
	sprite.move(dx);
}
