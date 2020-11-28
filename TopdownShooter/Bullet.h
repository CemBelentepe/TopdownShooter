#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:

public:
	Bullet(sf::Texture& texture)
		: GameObject(texture){}

};

