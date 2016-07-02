#include "cube.h"
#include "../buffer.h"
#include "../game.h"
#include "../shaderManager.h"
#include "../shaderProg.h"
#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <iostream>
using namespace std;

CubeObject::CubeObject(Game* game): Object(game)
{
	load();
}

CubeObject::~CubeObject()
{
	unload();
}

void CubeObject::load()
{
//	cout << "CubeObject::load() start" << endl;

	// Create the vertex, color, and index buffers
	vbo = new Buffer(Buffer::vbo, GL_FLOAT);
	cbo = new Buffer(Buffer::cbo, GL_FLOAT);
	ibo = new Buffer(Buffer::ibo, GL_UNSIGNED_INT);

	/* A cube's vertices
	 *    7----6
	 *   /|   /|
	 *  1----2 |  y  z
	 *  | 4--|-5  | /
	 *  |/   |/   |/
	 *  0----3    o----x
	 */

	GLfloat vertices[] =
	{
		-0.5f,	-0.5f,	-0.5f,	// 0
		-0.5f,	0.5f,	-0.5f,	// 1
		0.5f,	0.5f,	-0.5f,	// 2
		0.5f,	-0.5f,	-0.5f,	// 3
		-0.5f,	-0.5f,	0.5f,	// 4
		0.5f,	-0.5f,	0.5f,	// 5
		0.5f,	0.5f,	0.5f,	// 6
		-0.5f,	0.5f,	0.5f	// 7
	};
	GLfloat colors[] =
	{
		0,0,0,0.5f,	// 0
		0,1,0,0.5f,	// 1
		1,1,0,0.5f,	// 2
		1,0,0,0.5f,	// 3
		0,0,1,0.5f,	// 4
		1,0,1,0.5f,	// 5
		1,1,1,0.5f,	// 6
		0,1,1,0.5f		// 7
	};
	GLuint indices[] =
	{
		0,1,2, 0,2,3,	// Front
		4,5,6, 4,6,7,	// Back
		4,7,1, 4,1,0,	// Left
		3,2,6, 3,6,5,	// Right
		1,7,6, 1,6,2,	// Top
		5,4,0, 5,0,3	// Bottom
	};

	// Load the data into the buffers
	vbo->load(vertices, sizeof(vertices));
	cbo->load(colors, sizeof(colors));
	ibo->load(indices, sizeof(indices));
//	cout << "CubeObject::load() end" << endl;

	// Create a shaderProg in the shaderManager
	vector<string> shaderNames;
	shaderNames.push_back("shaders/vertex.glsl");
	shaderNames.push_back("shaders/fragment.glsl");
	ShaderManager* sm = get_game()->get_shader_manager();
	bool allGood = sm->add_shaderProg("cube", shaderNames);
	cout << "Did everything work? " << (allGood ? "Yup!" : "Nope! :(") << endl;
	if (!allGood)
		get_game()->quit();

	// Set the progID
	ShaderProg* sp = sm->get_shaderProg("cube");
	progID = sp->get_id();
	sp->print_attributes();
	sp->print_uniforms();
	GLuint modelID = sp->get_uniform("model");
}

void CubeObject::unload()
{
//	cout << "CubeObject::unload() start" << endl;
	delete vbo;
	delete cbo;
	delete ibo;
//	cout << "CubeObject::unload() end" << endl;
}
