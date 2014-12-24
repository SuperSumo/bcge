#include "manager.h"
#include "games/main_game.h"

int main(int argc, char** argv)
{
	// The manager does everything
	Manager manager;

	// Create a new Game object
	Game* initialGame = new MainGame(&manager);

	// Load the game into the manager which gets ownership of the pointer.
	manager.load_game(initialGame);

	cout << "main - returning" << endl;

	// We will return when the manager is done
	return 0;
}
