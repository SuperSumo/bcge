#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "abc/game.h"
#include "manager.h"

#include <gl/glew.h>
#include <SFML/Graphics.hpp>
#include "shader.h"

class GameMain: public Game
{
	public:

		GameMain(Manager* manager);
		~GameMain();

		virtual void load();
		virtual void update(float dt);
		virtual void interp(float dt);
		virtual void draw();

	private:

		GameMain();

		// TODO: Delete all of this stuff
		GLuint _vbo;
		GLuint _cbo;
		GLuint _shaderProgID;
		Shader* _vShader;
		Shader* _fShader;

};

#endif
