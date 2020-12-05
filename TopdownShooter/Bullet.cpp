#define _USE_MATH_DEFINES
#include <cmath>

#include "Bullet.h"
#include "Tilemap.h"

Bullet::Bullet(sf::Texture& texture, TileObject* tilemap)
	: SpriteObject(texture), speed(800), tilemap(tilemap)
{}

void Bullet::update(float deltaTime)
{
	sf::Vector2f dx(std::cos(sprite.getRotation() / 180 * M_PI),std::sin(sprite.getRotation() / 180 * M_PI));
	dx *= speed * deltaTime;
	sprite.move(dx);
}

bool Bullet::isAlive()
{
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2u size = Game::getWindow().getSize();
	return !tilemap->canCollide(pos) && pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y;
}
