#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "GameObject.h"

class Level
{
protected:
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> toAdd;
	std::unordered_map<std::string, sf::Texture> resources;

public:
	virtual ~Level(){}
	virtual void update(sf::RenderWindow& window, float deltaTime)
	{
		for (auto& go : toAdd)
			gameObjects.push_back(go);
		toAdd.clear();

		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			if (!gameObjects[i]->isAlive())
			{
				delete gameObjects[i];
				gameObjects.erase(gameObjects.begin() + i);
			}
		}

		for (auto& go : gameObjects)
			go->update(deltaTime);
	}
	virtual void render(sf::RenderWindow& window) 
	{
		for (auto& go : gameObjects)
			go->render(window);
	}
	virtual GameObject* addGameObject(GameObject* object)
	{
		toAdd.push_back(object);
		return object;
	}
	virtual sf::Texture& getTexture(const std::string& str)
	{
		return resources[str];
	}
};
