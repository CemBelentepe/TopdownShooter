#include "Game.h"
#include "Level.h"

#include "Level1.h"


int main()
{
	Game game(800, 600, "My Game!");
	Game::attachLevel(new Level1());
	Game::run();
	return 0;
}