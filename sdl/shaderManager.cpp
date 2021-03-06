#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "shaderManager.h"

using namespace std;

ShaderManager::~ShaderManager()
{
	clear();
}

void ShaderManager::clear()
{
	// Delete each shaderProg first
	ShaderProgMap::iterator i;
	for (i=_shaderProgs.begin(); i!=_shaderProgs.end(); i++)
		delete i->second;
	_shaderProgs.clear();

	// Then delete each shader
	ShaderMap::iterator j;
	for (j=_shaders.begin(); j!=_shaders.end(); j++)
		delete j->second;
	_shaders.clear();
}

bool ShaderManager::add_shader(GLenum type, string filename)
{
	// Make sure it doesn't exist.
	if (_shader_exists(filename))
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"ShaderManager::add_shader() - Shader %s already exists in the \
			ShaderManager @ %i", filename.c_str(), this);
		return false;
	}

	// Add the shader
	_shaders[filename] = new Shader(type);
	bool allGood = _shaders[filename]->load(filename);
	if (!allGood)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"ShaderManager::add_shader() - Shader %s couldn't be added to the \
			ShaderManager @ %i", filename.c_str(), this);
		delete _shaders[filename];
		_shaders.erase(filename);
	}
	return allGood;
}

bool ShaderManager::add_shaderProg(string progName, StringVec shaderFilenames)
{
	// Make sure it doesn't exist.
	if (_shaderProg_exists(progName))
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"ShaderManager::add_shaderProg() - ShaderProg %s already exists \
			in the ShaderManager @ %i", progName.c_str(), this);
		return false;
	}

	// Add the shaderProg
	_shaderProgs[progName] = new ShaderProg();

	// Go through each shader and add to the prog
	bool allGood = true;
	StringVec::iterator i;
	for (i=shaderFilenames.begin(); i!=shaderFilenames.end(); i++)
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_RENDER,
			"ShaderManager::add_shaderProg() - Adding %s to %s", (*i).c_str(),
			progName.c_str());
		if (!_shader_exists(*i))
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER,
				"ShaderManager::add_shaderProg() - ShaderProg %s doesn't \
				exist in the ShaderManager @ %i", (*i).c_str(), this);
			delete _shaderProgs[progName];
			_shaderProgs.erase(progName);
			return false;
		}
		else
			allGood &= _shaderProgs[progName]->add_shader(_shaders[*i]);
	}

	// If we were able to add all the shaders, try to compile
	if (allGood)
		allGood &= _shaderProgs[progName]->compile();

	return allGood;
}

ShaderProg* ShaderManager::get_shaderProg(string progName)
{
	if (_shaderProg_exists(progName))
		return _shaderProgs[progName];
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"ShaderManager::add_shaderProg() - ShaderProg %s doesn't \
			exist in the ShaderManager @ %i", progName.c_str(), this);
		return 0;
	}
}

bool ShaderManager::_shader_exists(string name)
{
	ShaderMap::iterator s = _shaders.find(name);
	return (s != _shaders.end());
}

bool ShaderManager::_shaderProg_exists(string name)
{
	ShaderProgMap::iterator s = _shaderProgs.find(name);
	return (s != _shaderProgs.end());
}
