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
		cerr << "ShaderManager::add_shader - Shader " << filename
			 << " already exists in the ShaderManager @ " << this << endl;
		return false;
	}

	// Add the shader
	_shaders[filename] = new Shader(type);
	bool allGood = _shaders[filename]->load(filename);
	if (!allGood)
	{
		cerr << "ShaderManager::add_shader - Shader " << filename
			 << " couldn't be added to ShaderManager @ " << this << endl;
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
		cerr << "ShaderManager::add_shaderProg - ShaderProg " << progName
			 << " already exists in the ShaderManager @ " << this << endl;
		return false;
	}

	// Add the shaderProg
	_shaderProgs[progName] = new ShaderProg();

	// Go through each shader and add to the prog
	bool allGood = true;
	StringVec::iterator i;
	for (i=shaderFilenames.begin(); i!=shaderFilenames.end(); i++)
	{
		cout << "Adding " << *i << " to " << progName << endl;
		if (!_shader_exists(*i))
		{
			cerr << "ShaderManager::add_shaderProg - Shader " << *i
				 << " doesn't exist in ShaderManager @ " << this << endl;
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
		cerr << "ShaderManager::get_shaderProg - ShaderProg " << progName
			 << " doesn't exist in ShaderManager @ " << this << endl;
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
