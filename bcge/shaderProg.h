#ifndef SHADERPROG_H
#define SHADERPROG_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#include <vector>
#include <map>
#include <string>
using namespace std;

typedef vector<Shader*> ShaderPVec;
typedef map<string, GLuint> AttributeMap;
typedef pair<string, GLuint> Attribute;
typedef map<string, GLuint> UniformMap;
typedef pair<string, GLuint> Uniform;

class ShaderProg
{
	public:
		ShaderProg(ShaderPVec shaders=ShaderPVec());
		~ShaderProg();

		bool add_shader(Shader* shader);
		bool reload();
		bool compile();
		GLuint get_id();
		ShaderPVec get_shaders();

		bool attribute_exists(string name);
		GLuint get_attribute(string name);

		bool uniform_exists(string name);
		GLuint get_uniform(string name);
		void set_uniform(string name, glm::mat4& value);

		void print_attributes();
		void print_uniforms();

		//TODO: Make methods to set attributes/uniforms

	private:
		GLuint id;
		ShaderPVec shaders;
		AttributeMap attributes;
		UniformMap uniforms;

		bool _make_attributes();
		bool _make_uniforms();
};

void print_program_log(GLint programID);

#endif
