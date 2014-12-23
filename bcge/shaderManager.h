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

		ShaderManager();
		~ShaderManager();

		bool reload();
		bool add_shader(GLenum type, string filename);
		bool add_shaderProg(string progName, StringVec shaderFilenames);
		ShaderProg* get_shaderProg(string progName);

	private:

		void _purge();
		bool _shader_exists(string name);
		bool _shaderProg_exists(string name);
		ShaderMap _shaders;
		ShaderProgMap _shaderProgs;
};

#endif

/*

ShaderManager::ShaderManager()
{
    _shaders is a map<string, Shader*>
    _shaderProgs is a map<string, ShaderProg*>
}

ShaderManager::reload()
{
    // Reload all the shaders and recompile the shaderprogs. I need this because when
    // I toggle fullscreen (creating a window) I will lose the OpenGL context, and all
    // the shaders and programs with it.

    // I need to save the current ShaderProgs. Make a map<string,vector<string> >
    // of shaderProgName:<shaders> so I can re-create the programs after
    // reloading the shaders
    shaderProgMap = map<string, vector<string> >;
    for shaderProg in shaderProgs:
        shaderProgMap[shaderProg->get_name()] = shaderProg->get_shader_names();

    // Delete all the shaderProgs

    // For each shader, call reload()

    // Recreate all the shaderProgs
    for shaderProg in ShaderProgMap:
        add_shader_prog(shaderProg.key(), shaderProg.value());
}

int ShaderManager::add_shader(type, filename)
{
    _shaders[filename] = new Shader(type);
    return _shaders[filename]->load_from_file(filename);
}

int ShaderManager::add_shader_prog(string shaderProgName, vector<string> shaderNames)
{
    _shaderProgs[shaderProgName] = new ShaderProg();
    for shaderName in shaderNames:
        // If the shader doesn't exist in the _shaders vector, try to add it
        // Attach the shader to the shader prog
        _shaderProgs[shaderProgName]->attach_shader(_shaders[shaderName]);
    // Compile the shaderProg
    // Return the compilation status
}

// All of these functions will automatically bind the correct
// shaderProg and have a "if _curProg != shaderProgName: bind(shaderProgName)"
// so there aren't as many context switches
int ShaderManager::set_uniform(shaderProgName, glm::mat4& value);
int ShaderManager::set_uniform(shaderProgName, glm::mat3& value);
int ShaderManager::set_uniform(shaderProgName, glm::vec3& value); //
etc...same with attributes

*/
