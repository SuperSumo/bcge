#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "defines_constants_typedefs.h"

#include "shader.h"
#include "shaderProg.h"

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
