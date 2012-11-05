#ifndef OBJECT_H
#define OBJECT_H

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>

class Game;
class Buffer;

class Object
{
	public:
		Object(Game* game);
		virtual ~Object();

		Game* get_game();
		virtual void load()=0;
		virtual void unload()=0;
		virtual void reload();
		GLuint get_progID();
		virtual void draw();

	protected:
		Game* game;
		Buffer* vbo;
		Buffer* ibo;
		Buffer* cbo;
		GLuint progID;
};

#endif
