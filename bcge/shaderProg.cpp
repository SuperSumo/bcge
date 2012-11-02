#include "shaderProg.h"
#include <vector>
#include <iostream>
#include <string>
#include <map>
using namespace std;

void print_program_log(GLint programID)
{
	int maxLength = 0;
	int length = 0;
	char* infoLog;

	// Get the max length of an info log
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

	// Grab the info log
	if(maxLength)
	{
		infoLog = new char[maxLength];
		glGetProgramInfoLog(programID, maxLength, &length, infoLog);
		cerr << infoLog << endl;
		delete [] infoLog;
	}
}

ShaderProg::ShaderProg(ShaderPVec shaders):
		id(-1), shaders(shaders),
		attributes(AttributeMap()), uniforms(UniformMap())
{
	if (shaders.size())
		reload();
}

ShaderProg::~ShaderProg()
{
	if (id != -1) glDeleteProgram(id);
}

bool ShaderProg::add_shader(Shader* shader)
{
	if (shader->get_id() != -1)
	{
		shaders.push_back(shader);
		return true;
	}
	else
	{
		cerr << "Error: The shader was not compiled correctly!" << endl;
		return false;
	}
}

bool ShaderProg::reload()
{
	// Make sure all the shaders get reloaded
	ShaderPVec::iterator i;
	bool areShadersGood = true;
	for (i=shaders.begin(); i!=shaders.end(); i++)
		areShadersGood &= (*i)->reload();

	// If a shader failed to compile, bail out and keep the current program
	if (!areShadersGood) return false;

	// The shaders are good, let's (re)create the program.
	return compile();
}

bool ShaderProg::compile()
{
	// TODO: I think I might want to ensure at least vertex and fragment shaders
	// are present for a ShaderProg to compiler correctly. Otherwise, what's the
	// point of having one? I would need to check the type while I go through
	// attaching the shaders.

	// If the program exists, delete it
	if (id != -1) glDeleteProgram(id);

	// Create a new program id
	id = glCreateProgram();

	// Attach each shader
	ShaderPVec::iterator i;
	for (i=shaders.begin(); i!=shaders.end(); i++)
		glAttachShader(id, (*i)->get_id());

	// Link the program
	glLinkProgram(id);

	// Check the linking status
	GLint isLinked;
	glGetProgramiv(id, GL_LINK_STATUS, &isLinked);

	// If no good, say so, say why, and delete it
	if (!isLinked)
	{
		cerr << "Error! Shader program not compiled: " << id << endl;
		print_program_log(id);
		glDeleteProgram(id);
		id = -1;
		return false;
	}

	// Create the attributes and uniforms maps
	if (!_make_attributes()) return false;
	if (!_make_uniforms()) return false;

	// Yay!
	return true;
}

GLuint ShaderProg::get_id()
{
	return id;
}

ShaderPVec ShaderProg::get_shaders()
{
	return shaders;
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
	glGetProgramiv(get_id(), GL_ACTIVE_ATTRIBUTES, &numAttribs);
	// Get the max length of an attribute's name
	glGetProgramiv(get_id(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

	// Grab the attributes
	for (int i=0; i<numAttribs; i++)
	{
		name = new char[maxLength];
		// Get the name
		glGetActiveAttrib(get_id(), i, maxLength, &length, &size, &type, name);
		// Insert a new Attribute
		ret = attributes.insert(Attribute(name, glGetAttribLocation(get_id(), name)));
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

bool ShaderProg::attribute_exists(string name)
{
	AttributeMap::iterator s = attributes.find(name);
	if (s == attributes.end())
	{
		cerr	<< "ShaderProg::attribute_exists - Attribute " << name
				<< " doesn't exist in the ShaderProg @ " << this << endl;
		return false;
	}
	return true;
}

GLuint ShaderProg::get_attribute(string name)
{
	if (attribute_exists(name))
		return attributes[name];
	return -1;
}

void ShaderProg::print_attributes()
{
	for (AttributeMap::iterator i=attributes.begin(); i!=attributes.end(); i++)
		cout << i->second << "\t" << i->first << endl;
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
	glGetProgramiv(get_id(), GL_ACTIVE_UNIFORMS, &numUniforms);
	// Get the max length of a uniform's name
	glGetProgramiv(get_id(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	// Grab the uniforms
	for (int i=0; i<numUniforms; i++)
	{
		name = new char[maxLength];
		// Get the name
		glGetActiveUniform(get_id(), i, maxLength, &length, &size, &type, name);
		// Insert a new Uniform
		ret = uniforms.insert(Uniform(name, glGetUniformLocation(get_id(), name)));
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

bool ShaderProg::uniform_exists(string name)
{
	UniformMap::iterator s = uniforms.find(name);
	if (s == uniforms.end())
	{
		cerr	<< "ShaderProg::uniform_exists - Uniform " << name
				<< " doesn't exist in the ShaderProg @ " << this << endl;
		return false;
	}
	return true;
}

GLuint ShaderProg::get_uniform(string name)
{
	if (uniform_exists(name))
		return uniforms[name];
	return -1;
}

void ShaderProg::set_uniform(string name, glm::mat4& value)
{
	// TODO: I need to make more of these for each type of value
	if (uniform_exists(name))
		glUniformMatrix4fv(uniforms[name], 1, false, glm::value_ptr(value));
}

void ShaderProg::print_uniforms()
{
	for (UniformMap::iterator i=uniforms.begin(); i!=uniforms.end(); i++)
		cout << i->second << "\t" << i->first << endl;
}
