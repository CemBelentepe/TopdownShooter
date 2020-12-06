#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Level;
class GameObject;
class Game
{
private:
	static Game* instance;
	
	sf::RenderWindow window;
	Level* level;
	Level* nextLevel;
public:
	Game(unsigned int width, unsigned int height, const char* title);

	Game(const Game&) = delete;

	static void run();

	static sf::Vector2i getMousePosition();
	static void attachLevel(Level* level);
	static Game* getInstance();
	static GameObject* addGameObject(GameObject* go);
	static sf::Texture& getTexture(const std::string& str);

	static const sf::RenderWindow& getWindow();
};
