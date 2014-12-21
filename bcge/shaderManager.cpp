#include "shaderManager.h"

ShaderManager::ShaderManager()
{}

ShaderManager::~ShaderManager()
{
	_purge();
}

bool ShaderManager::reload()
{
	// Reload all the shaders
	// Reload all the shader progs
	return true;
}

void ShaderManager::_purge()
{
	// Delete each shaderProg first
	// Then delete each shader
}

bool ShaderManager::add_shader(GLenum type, string filename)
{
	// TODO: Add the shader here. Make sure it doesn't exist.
	return true;
}

bool ShaderManager::add_shaderProg(string progName, StringVec shaderFilenames)
{
	// TODO: Add a shader prog here. Make sure it doesn't exist.
	return true;
}

ShaderProg* ShaderManager::get_shaderProg(string progName)
{
	return 0;
}

bool ShaderManager::_shader_exists(string name)
{
	ShaderMap::iterator s = _shaders.find(name);
	if (s == _shaders.end())
	{
		cerr	<< "ShaderManager::_shader_exists - Shader " << name
				<< " doesn't exist in the ShaderManager @ " << this << endl;
		return false;
	}
	return true;
}

bool ShaderManager::_shaderProg_exists(string name)
{
	ShaderProgMap::iterator s = _shaderProgs.find(name);
	if (s == _shaderProgs.end())
	{
		cerr	<< "ShaderManager::_shaderProg_exists - ShaderProg " << name
				<< " doesn't exist in the ShaderManager @ " << this << endl;
		return false;
	}
	return true;
}
