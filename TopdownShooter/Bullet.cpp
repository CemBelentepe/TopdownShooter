#define _USE_MATH_DEFINES
#include <cmath>

#include "Bullet.h"
#include "Tilemap.h"
#include "Animation.h"

Bullet::Bullet(sf::Texture& texture, TileObject* tilemap, int tag)
	: SpriteObject(texture, tag), speed(800), tilemap(tilemap)
{}

void Bullet::update(float deltaTime)
{
	sf::Vector2f dx(std::cos(sprite.getRotation() / 180 * M_PI),std::sin(sprite.getRotation() / 180 * M_PI));
	dx *= speed * deltaTime;
	sprite.move(dx);

	if (tilemap->canCollide(sprite.getPosition()))
	{
		AnimObject* anim = new AnimObject(Game::getTexture("explosion"), 8, 0.04f);
		anim->sprite.setPosition(sprite.getPosition());
		anim->sprite.setScale(0.5f, 0.5f);
		Game::addGameObject(anim);
	}
}

bool Bullet::isAlive()
{
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2u size = Game::getWindow().getSize();
	return health > 0 && !tilemap->canCollide(pos) && pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y;
}
