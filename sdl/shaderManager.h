#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <map>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "defines_constants_typedefs.h"
#include "shader.h"
#include "shaderProg.h"

using namespace std;

typedef map<string, ShaderProg*> ShaderProgMap;
typedef map<string, Shader*> ShaderMap;

class ShaderManager
{
	public:

		~ShaderManager();

		void clear();
		bool add_shader(GLenum type, string filename);
		bool add_shaderProg(string progName, StringVec shaderFilenames);
		ShaderProg* get_shaderProg(string progName);

	private:

		bool _shader_exists(string name);
		bool _shaderProg_exists(string name);
		ShaderMap _shaders;
		ShaderProgMap _shaderProgs;
};

#endif
