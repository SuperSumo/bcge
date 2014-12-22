#ifndef SHADERPROG_H
#define SHADERPROG_H

#include "shader.h"
#include "defines_constants_typedefs.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef vector<Shader* >ShaderVec;
typedef map<string, Shader*> ShaderMap;
typedef map<string, GLuint> AttributeMap;
typedef map<string, GLuint> UniformMap;
typedef pair<string, GLuint> Attribute;
typedef pair<string, GLuint> Uniform;

class ShaderProg
{
	public:

		ShaderProg(string name);
		~ShaderProg();

		bool add_shader(Shader* shader);
		bool compile();
		GLuint get_id();
		string get_name();
		GLuint get_attribute(string attributeName);
		GLuint get_uniform(string uniformName);

	private:

		ShaderProg();
		void _print_log();
		bool _attribute_exists(string name);
		bool _uniform_exists(string name);
		bool _make_attributes();
		bool _make_uniforms();
		GLuint _id;
		string _name;
		ShaderMap _shaders;
		AttributeMap _attributes;
		UniformMap _uniforms;
};

#endif