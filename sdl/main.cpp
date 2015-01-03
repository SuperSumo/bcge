#include "manager.h"
#include "games/main_game.h"

int main(int argc, char** argv)
{
	// Create and initialize the manager
	Manager manager;
	if (!manager.init())
		return 1;

	// Create and initialize a game
	MainGame* game = new MainGame(&manager);
	if (!game->_init())
		return 2;

	// Load the game which starts the main loop
	manager.load_game(game);
	manager.start_main_loop();

	return 0;
}
