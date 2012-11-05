#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "shaderManager.h"
#include "shader.h"
#include "shaderProg.h"
#include "defines.h"

ShaderManager::ShaderManager(){}
ShaderManager::~ShaderManager()
{
	// TODO: Delete all the shaders and shaderProgs from the map
	map<string, Shader*>::iterator s;
	for (s=shaders.begin(); s!=shaders.end(); s++)
		delete s->second;
	map<string, ShaderProg*>::iterator sp;
	for (sp=shaderProgs.begin(); sp!=shaderProgs.end(); sp++)
		delete sp->second;
}

bool ShaderManager::add_shader(string filename, GLenum type)
{
	bool allGood = true;
	// Create an iterator boolean thing to use and test if the insert worked
	pair<map<string,Shader*>::iterator,bool> ret;
	Shader* shader = new Shader(type);
	allGood &= shader->load_from_file(filename);
	ret = shaders.insert(pair<string, Shader*>(filename, shader));
	if (!ret.second)
	{
		cerr	<< "ShaderManager::add_shader - Shader \""
				<< filename
				<< "\" already exists." << endl;
//		return false;
	}
	return allGood;
}

Shader* ShaderManager::get_shader(string filename)
{
	map<string, Shader*>::iterator s = shaders.find(filename);
	// If the shader was found return it, else return 0
	return (s!=shaders.end() ? s->second : 0);
}

bool ShaderManager::delete_shader(string filename)
{
	// TODO: Make sure to recompile any shaderProg this shader uses
	map<string, Shader*>::iterator s = shaders.find(filename);
	if (s!=shaders.end())
	{
		delete s->second;
		shaders.erase(s);
		return true;
	}
	return false;
}

void ShaderManager::print_shaders()
{
	map<string, Shader*>::iterator s;
	for (s=shaders.begin(); s!=shaders.end(); s++)
		cout << s->first << " = " << s->second << endl;
}

bool ShaderManager::add_shaderProg(string shaderProgName, vector<string> shaderNames)
{
	bool allGood = true;
	// Create an iterator boolean thing to use and test if the insert worked
	pair<map<string,ShaderProg*>::iterator,bool> ret;
	ShaderProg* shaderProg = new ShaderProg;
	// Insert a new ShaderProg
	ret = shaderProgs.insert(pair<string, ShaderProg*>(shaderProgName, shaderProg));
	if (!ret.second)
	{
		cerr	<< "ShaderManager::add_shaderProg - ShaderProg "
				<< shaderProgName
				<< " already exists." << endl;
		shaderProgs.erase(ret.first);
		return false;
	}

	// If there are shaders, add them
	StringVec::iterator i;
	if (shaders.size())
		for (i=shaderNames.begin(); i!=shaderNames.end(); i++)
		{
			cout << "Adding " << *i << " to " << shaderProgName << endl;
			map<string, Shader*>::iterator s = shaders.find(*i);
			if (s == shaders.end())
			{
				cerr	<< "ShaderManager::add_shaderProg - Shader \""
						<< *i
						<< "\" doesn't exist in the shader manager." << endl;
				shaderProgs.erase(ret.first);
				return false;
			}
			else
				allGood &= shaderProg->add_shader(shaders[*i]);
		}
		// Check if the compilation went ok
		if (allGood) allGood &= shaderProg->compile();

	return allGood;
}
ShaderProg* ShaderManager::get_shaderProg(string shaderProgName)
{
	map<string, ShaderProg*>::iterator s = shaderProgs.find(shaderProgName);
	if (s == shaderProgs.end())
	{
		cerr	<< "ShaderManager::get_shaderProg - ShaderProg \""
				<< shaderProgName
				<< "\" doesn't exist in the shader manager." << endl;
		return 0;
	}
	return s->second;
}

bool ShaderManager::reload_shaderProg(string shaderProgName)
{
	// TODO: finish ShaderManager::reload_shaderProg
	return true;
}

bool ShaderManager::delete_shaderProg(string shaderProgName)
{
	// TODO: finish ShaderManager::delete_shaderProg
	return true;
}

bool ShaderManager::add_shader_to_shaderProg(string filename, string shaderProgName)
{
	// TODO: finish ShaderManager::add_shader_to_shaderProg
	return true;
}

void ShaderManager::print_shaderProgs()
{
	map<string, ShaderProg*>::iterator s;
	for (s=shaderProgs.begin(); s!=shaderProgs.end(); s++)
		cout << s->first << " = " << s->second << endl;
}
