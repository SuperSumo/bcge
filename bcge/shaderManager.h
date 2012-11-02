#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include <map>
#include <string>
#include <vector>
using namespace std;

#include "defines.h"

class Shader;
class ShaderProg;

/* TODO: Create a ShaderManager class. That way, I can have multiple
objects point to the same shaderProg, and if one of them calls needs to
recompile it's shader, all the objects using that shaderProg would get
updated without having to each call their recompile.
The ShaderManager would have a map to the different shaderProgs.
std::map<string "name", ShaderProg* prog> shaderProgs;
shaderProgs["name"]->get_id() or
shaderProgs["name"]->recompile()
I would need a map to shaders (key is filename). I could even look
through the folder and create Shader objects automatically that way.
std::map<string "name", Shader* shader> shaders;
ShaderManager
- shaders
- shaderProgs
void make_shader_prog(string name, vector<Shader*> shadersToAdd)
{
	shaderProgs.add(name);
	for shader in shadersToAdd:
		shaderProgs[name].add_shader(shader)
	shaderProgs[name].compile()
}
Object
- ShaderProg* shaderProg = shaderProgs["fragment.glsl"]; */

class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();

		bool add_shader(string filename, GLenum type);
		Shader* get_shader(string filename);
		bool delete_shader(string filename);
		void print_shaders();

		bool add_shaderProg(string shaderProgName, StringVec shaderNames=StringVec());
		ShaderProg* get_shaderProg(string shaderProgName);
		bool reload_shaderProg(string shaderProgName);
		bool delete_shaderProg(string shaderProgName);
		bool add_shader_to_shaderProg(string shaderName, string shaderProgName);
		void print_shaderProgs();

	private:
		map<string, Shader*> shaders;
		map<string, ShaderProg*> shaderProgs;
};

#endif
