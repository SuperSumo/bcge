#ifndef GAME_H
#define GAME_H

class Manager;
class Input;

class Game
{
	public:

		Game(Manager* manager);
		virtual ~Game();
		bool _init(); // The init used by the main function, which calls init

		virtual bool init()=0;
		virtual void update(float dt)=0;
		virtual void interp(float dt)=0;

		Manager* get_manager();
		Input* get_input();

		// TODO: Delete this:
		virtual void draw_delete_me()=0;

	protected:

		Manager* _manager;
		Input* _input;

	private:

		Game();
};

#endif
