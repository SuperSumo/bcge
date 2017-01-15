#include <iostream>
#include <map>
#include <vector>
#include <utility>

#include "shaderProg.h"
#include "shaderManager.h"
#include "shader.h"
#include "defines_constants_typedefs.h"
#include "utils.h"

using namespace std;

ShaderProg::ShaderProg():
	_id(-1)
{}

bool ShaderProg::add_shader(Shader* shader)
{
	// Ownership of the shader object is in the shader manager
	if (shader->get_id() == -1)
	{
		cerr << "Error: The shader was not compiled correctly!" << endl;
		return false;
	}
	_shaders[shader->get_filename()] = shader;
	return true;
}

bool ShaderProg::compile()
{
	// If the program exists, delete it
	if (_id != -1) glDeleteProgram(_id);

	// Create a new program id
	_id = glCreateProgram();

	// Attach each shader
	for (ShaderMap::iterator i=_shaders.begin(); i!=_shaders.end(); i++)
		glAttachShader(_id, (*i).second->get_id());

	// Link the program
	glLinkProgram(_id);

	// Check the linking status
	GLint isLinked;
	glGetProgramiv(_id, GL_LINK_STATUS, &isLinked);

	// If no good, say so, say why, and delete it
	if (!isLinked)
	{
		cerr << "Error! Shader program not compiled: " << _id << endl;
		_print_log();
		glDeleteProgram(_id);
		_id = -1;
		return false;
	}

	// Create the attributes and uniforms maps
	if (!_make_attributes()) return false;
	if (!_make_uniforms()) return false;

	// Yay!
	return true;
}

bool ShaderProg::_make_attributes()
{
	GLint numAttribs = 0;	// The number of attributes
	GLsizei maxLength = 0;	// The maximum length of a name
	GLsizei length = 0;		// The length of the name of the attribute
	GLint size = 0;			// The number of bytes of the attribute
	GLenum type;			// The type of the attribute
	char* name;				// The name of the attribute
	GLint location;			// The location of the attribute within the program
	pair<AttributeMap::iterator,bool> ret;	// The return value of the insert

	// Get the number of attributes
	glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES, &numAttribs);
	// Get the max length of an attribute's name
	glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

	// Grab the attributes
	for (int i=0; i<numAttribs; i++)
	{
		name = new char[maxLength];
		// Get the name
		glGetActiveAttrib(_id, i, maxLength, &length, &size, &type, name);
		// Insert a new Attribute
		ret = _attributes.insert(Attribute(name, glGetAttribLocation(_id, name)));
		if (!ret.second)
		{
			cerr	<< "ShaderProg::_make_attributes - Attribute " << name
					<< " already exists in the ShaderProg @ " << this << endl;
		}
		delete [] name;
		if (!ret.second) return false;
	}
	return true;
}

bool ShaderProg::_attribute_exists(string name)
{
	AttributeMap::iterator s = _attributes.find(name);
	if (s == _attributes.end())
	{
		cerr	<< "ShaderProg::attribute_exists - Attribute " << name
				<< " doesn't exist in the ShaderProg @ " << this << endl;
		return false;
	}
	return true;
}

GLuint ShaderProg::get_attribute(string name)
{
	if (_attribute_exists(name))
		return _attributes[name];
	return -1;
}

bool ShaderProg::_make_uniforms()
{
	GLint numUniforms = 0;	// The number of uniforms
	GLsizei maxLength = 0;	// The maximum length of a name
	GLsizei length = 0;		// The length of the name of the uniform
	GLint size = 0;			// The number of bytes of the uniform
	GLenum type;			// The type of the uniform
	char* name;				// The name of the uniform
	GLint location;			// The location of the uniform within the program
	pair<UniformMap::iterator,bool> ret;	// The return value of the insert

	// Get the number of uniforms
	glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &numUniforms);
	// Get the max length of a uniform's name
	glGetProgramiv(_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	// Grab the uniforms
	for (int i=0; i<numUniforms; i++)
	{
		name = new char[maxLength];
		// Get the name
		glGetActiveUniform(_id, i, maxLength, &length, &size, &type, name);
		// Insert a new Uniform
		ret = _uniforms.insert(Uniform(name, glGetUniformLocation(_id, name)));
		if (!ret.second)
		{
			cerr	<< "ShaderProg::_make_uniforms - Uniform " << name
					<< " already exists in the ShaderProg @ " << this << endl;
		}
		delete [] name;
		if (!ret.second) return false;
	}
	return true;
}

bool ShaderProg::_uniform_exists(string name)
{
	UniformMap::iterator s = _uniforms.find(name);
	if (s == _uniforms.end())
	{
		cerr	<< "ShaderProg::uniform_exists - Uniform " << name
				<< " doesn't exist in the ShaderProg @ " << this << endl;
		return false;
	}
	return true;
}

GLuint ShaderProg::get_uniform(string name)
{
	if (_uniform_exists(name))
		return _uniforms[name];
	return -1;
}

GLuint ShaderProg::get_id()
{
	return _id;
}

void ShaderProg::_print_log()
{
	int maxLength = 0;
	int length = 0;
	char* infoLog;

	// Get the max length of an info log
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &maxLength);

	// Grab the info log
	if(maxLength)
	{
		infoLog = new char[maxLength];
		glGetProgramInfoLog(_id, maxLength, &length, infoLog);
		cerr << infoLog << endl;
		delete [] infoLog;
	}
}
