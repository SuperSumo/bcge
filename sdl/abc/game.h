#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>

#include "../shaderManager.h"

using namespace std;

class Manager;
class Input;

class Game
{
	public:

		Game(Manager* manager);
		virtual ~Game();

		virtual bool init()=0;
		virtual void update(float dt)=0;
		virtual void interp(float dt)=0;

		Manager* get_manager();
		Input* get_input(string name=string());

		// TODO: Delete this:
		virtual void draw_delete_me()=0;

	protected:

		Manager* _manager;
		Input* _input;
		ShaderManager shaderManager;

	private:

		Game();
};

#endif
