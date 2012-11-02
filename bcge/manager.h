#ifndef MANAGER_H_
#define MANAGER_H_

class Game;
class Window;

class Manager
{
	public:

		Manager(int argc, char** argv, Game* initialGame=0);
		~Manager();

		void set_game(Game* gameToSet);
		Game* get_game();
		Window* get_window();

	private:

		Window* window;
		Game* game;
};

#endif /* MANAGER_H_ */
