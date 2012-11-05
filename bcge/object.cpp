#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include "object.h"
#include "game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "buffer.h"
#include "camera.h"
#include "renderer.h"

Object::Object(Game* game): game(game), vbo(0), ibo(0), cbo(0), progID(-1)
{}

Object::~Object()
{}

Game* Object::get_game()
{
	return game;
}

void Object::reload()
{
	unload();
	load();
}

GLuint Object::get_progID()
{
	return progID;
}

void Object::draw()
{
	if (get_progID() != -1)
	{
		if (vbo)
		{
			// associate position input to shader with position array in vertex buffer
			GLuint vPosition = glGetAttribLocation(get_progID(), "inVertex");
			glEnableVertexAttribArray(vPosition);
			glBindBuffer(GL_ARRAY_BUFFER, vbo->get_id());
			glVertexAttribPointer(vPosition, /*xyz*/3, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (cbo)
		{
			// associate color input to shader with color array in vertex buffer
			GLuint vColor = glGetAttribLocation(get_progID(), "inColor");
			glEnableVertexAttribArray(vColor);
			glBindBuffer(GL_ARRAY_BUFFER, cbo->get_id());
			glVertexAttribPointer(vColor, /*rgba*/4, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// Use the vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo->get_id());
		glVertexPointer(/*xyz*/3, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Use the color buffer
		glBindBuffer(GL_ARRAY_BUFFER, cbo->get_id());
		glColorPointer(/*rgba*/4, GL_FLOAT, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Apply the camera
		get_game()->get_camera()->apply_to_shader(get_progID());

		// Draw from the buffers
		if (ibo && ibo->get_id() != -1) ibo->draw();
		else if (vbo && vbo->get_id() != -1) vbo->draw();
	}
}
