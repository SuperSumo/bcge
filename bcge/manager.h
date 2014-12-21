#ifndef MANAGER_H
#define MANAGER_H

#include "shader.h"

class Game;
class Window;
class Renderer;

class Manager
{
	public:

		Manager();
		~Manager();

		void draw();
		void load_game(Game* gameToSet);

		Window* get_window();
		Renderer* get_renderer();
		Game* get_game();

	private:

		void _main_loop();
		void _handle_events();

		Window* _window;
		Renderer* _renderer;
		Game* _game;

		// TODO: Delete all of this stuff
		GLuint _vbo;
		GLuint _cbo;
		GLuint _shaderProgID;
		Shader* _vShader;
		Shader* _fShader;

};

#endif
