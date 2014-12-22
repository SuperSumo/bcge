#include "manager.h"
#include "games/main.h"

int main(int argc, char** argv)
{
	// The manager does everything
	Manager manager;

	// Create a new Game object
	Game* initialGame = new GameMain(&manager);

	// Load the game into the manager which gets ownership of the pointer.
	manager.load_game(initialGame);

	// We will return when the manager is done
	return 0;
}
