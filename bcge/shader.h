#ifndef SHADER_H
#define SHADER_H

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include "defines_constants_typedefs.h"
#include <iostream>
#include <string>

using namespace std;

class Shader
{
	public:
		// type can be GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
		// GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
		Shader(GLenum type);
		~Shader();

		bool load(string filename);
		bool reload();
		GLuint get_id();
		string get_filename();

	private:
		Shader();
		void _print_log();
		GLuint _id;
		GLenum _type;
		string _filename;
		string _source;
};

#endif
