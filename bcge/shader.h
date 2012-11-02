#ifndef SHADER_H
#define SHADER_H

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <sstream>
using namespace std;

class Shader
{
	public:
		// type can be GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
		// GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, or GL_FRAGMENT_SHADER
		Shader(GLenum type);
		~Shader();

		bool load_from_file(string file);
		bool reload();
		GLuint get_id();
		GLenum get_type();
		string get_filename();
		void print();

	private:
		GLuint id;
		GLenum type;
		string filename, source;
};

void print_shader_log(GLint shaderID);

#endif
