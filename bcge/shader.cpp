// TODO: http://www.opengl.org/wiki/Tutorial1:_Rendering_shapes_with_glDrawRangeElements,_VAO,_VBO,_shaders_%28C%2B%2B_/_freeGLUT%29
// TODO: http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include "shader.h"
#include "defines.h"
#include "utils.h"
#include <sstream>
#include <iostream>
using namespace std;

void print_shader_log(GLint shaderID)
{
	int maxLength = 0;
	int length = 0;
	char* infoLog;

	// Get the max length of an info log
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

	// Grab the info log
	if (maxLength)
	{
		infoLog = new char[maxLength];
		glGetShaderInfoLog(shaderID, maxLength, &length, infoLog);
		cerr << infoLog << endl;
		delete [] infoLog;
	}
}

Shader::Shader(GLenum type):
		id(-1), type(type), filename(""), source("")
{}

Shader::~Shader()
{
	if (id != -1) glDeleteShader(id);
}

bool Shader::load_from_file(string file)
{
	// A temporary string of the source
	string tempSource;
	bool isGoodRead = read_text_file(file, tempSource);
	int length = tempSource.length();

	// If the file is empty or the read failed, peace out
	if(tempSource.empty() || !isGoodRead)
		return false;

	// If the shader exists, delete it
	if (id != -1) glDeleteShader(id);

	// Create a new shader id
	id = glCreateShader(type);

	// Convert the source to the correct format and upload to GPU
	const char *constSource = tempSource.c_str();
	glShaderSource(id, 1, (const char**)&constSource, &length);

	// Compile the shader on the GPU
	glCompileShader(id);

	// Check the compilation status
	GLint isCompiled; // Returns a boolean value, but must pass an int
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled)
	{
		cerr << "Error! Shader not compiled: " << file << endl;
		print_shader_log(id);
		glDeleteShader(id);
		id = -1;
		return false;
	}

	// Everything was good, so copy things over permanently
	source = tempSource;
	filename = file;
	return true;
}

bool Shader::reload()
{
	return load_from_file(filename);
}

GLuint Shader::get_id()
{
	return id;
}

string Shader::get_filename()
{
	return filename;
}

void Shader::print()
{
	cout << "Shader: " << filename << endl << source << endl;
}
