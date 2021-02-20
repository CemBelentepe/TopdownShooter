#include "Game.h"
#include "Level.h"
#include <chrono>

Game* Game::instance = nullptr;

Game::Game(unsigned int width, unsigned int height, const char* title)
	:window(sf::VideoMode(width, height), title), level(nullptr), nextLevel(nullptr)
{
	instance = this;
}

void Game::run()
{
	float deltaTime;
	auto t1 = std::chrono::high_resolution_clock::now();
	while (instance->window.isOpen())
	{
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> dt = t2 - t1;
		deltaTime = dt.count();
		t1 = t2;

		sf::Event event;
		while (instance->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				instance->window.close();
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					instance->window.close();
		}

		if (instance->nextLevel)
		{
			delete instance->level;
			instance->level = instance->nextLevel;
			instance->nextLevel = nullptr;
		}

		instance->level->update(deltaTime);

		instance->window.clear();
		instance->level->render(instance->window, deltaTime);
		instance->window.display();
	}
}

sf::Vector2i Game::getMousePosition()
{
	return sf::Mouse::getPosition(instance->window);
}

void Game::attachLevel(Level* level)
{
	instance->nextLevel = level;
}

Game* Game::getInstance()
{
	return instance;
}

GameObject* Game::addGameObject(GameObject* go)
{
	return instance->level->addGameObject(go);
}

sf::Texture& Game::getTexture(const std::string& str)
{
	return instance->level->getTexture(str);
}

const Level* Game::getLevel()
{
	return instance->level;
}

std::vector<GameObject*> Game::getGameObjectsWithTag(int tag)
{
	return instance->level->getGameObjectsWithTag(tag);
}

std::vector<GameObject*> Game::getGameObjectsWithTags(std::vector<int> tagList)
{
	return instance->level->getGameObjectsWithTags(tagList);
}

const sf::RenderWindow& Game::getWindow()
{
	return instance->window;
}
