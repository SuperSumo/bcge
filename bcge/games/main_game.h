#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../abc/game.h"
#include "../buffer.h"

class Manager;

class MainGame: public Game
{
	public:

		MainGame(Manager* manager);
		virtual ~MainGame();

		virtual void load();
		virtual void update(float dt);
		virtual void interp(float dt);
		virtual void draw();

	private:

		MainGame();

		// TODO: Delete all of this stuff
		// GLuint _vbo;
		// GLuint _cbo;
		Buffer* _vbo;
		Buffer* _cbo;
		Buffer* _ibo;
		float _fov, _nearView, _farView;
		glm::mat4 _projection, _view;
		glm::vec3 _rotV, _pos;

};

#endif
