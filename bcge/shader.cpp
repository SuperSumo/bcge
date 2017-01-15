#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include <sstream>
#include <iostream>

#include "shader.h"
#include "defines_constants_typedefs.h"
#include "utils.h"

using namespace std;

Shader::Shader(GLenum type):
		_id(-1), _type(type), _filename(""), _source("")
{}

Shader::~Shader()
{
	if (_id != -1) glDeleteShader(_id);
}

void Shader::_print_log()
{
	int maxLength = 0;
	int length = 0;
	char* infoLog;

	// Get the max length of an info log
	glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &maxLength);

	// Grab the info log
	if (maxLength)
	{
		infoLog = new char[maxLength];
		glGetShaderInfoLog(_id, maxLength, &length, infoLog);
		cerr << infoLog << endl;
		delete [] infoLog;
	}
}

bool Shader::load(string file)
{
	// A temporary string of the source
	string tempSource;
	bool isGoodRead = read_text_file(file, tempSource);
	int length = tempSource.length();

	// If the file is empty or the read failed, peace out
	if(tempSource.empty() || !isGoodRead)
		return false;

	// If the shader exists, delete it
	if (_id != -1) glDeleteShader(_id);

	// Create a new shader id
	_id = glCreateShader(_type);

	// Convert the source to the correct format and upload to GPU
	const char *constSource = tempSource.c_str();
	glShaderSource(_id, 1, (const char**)&constSource, &length);

	// Compile the shader on the GPU
	glCompileShader(_id);

	// Check the compilation status
	GLint isCompiled; // Returns a boolean value, but must pass an int
	glGetShaderiv(_id, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled)
	{
		cerr << "Error! Shader not compiled: " << file << endl;
		_print_log();
		glDeleteShader(_id);
		_id = -1;
		return false;
	}

	// Everything was good, so copy things over permanently
	_source = tempSource;
	_filename = file;
	return true;
}

bool Shader::reload()
{
	return load(_filename);
}

GLuint Shader::get_id()
{
	return _id;
}

string Shader::get_filename()
{
	return _filename;
}
