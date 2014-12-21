#ifndef RENDERER_H
#define RENDERER_H

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include "defines_constants_typedefs.h"
#include "shader.h"
#include "shaderManager.h"

class Manager;

class Renderer
{
	public:

		Renderer(Manager* manager);
		void initialize();
		void render();

	private:

		Renderer();

		Manager* _manager;
};

#endif
