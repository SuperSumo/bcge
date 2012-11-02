#include "manager.h"
#include "game.h"

#include "shader.h"
#include "shaderProg.h"
#include "shaderManager.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "renderer.h"

int main(int argc, char** argv)
{
	// TODO: Update the camera's view/perspective matrices in every shader
	// program when they change or upload them each frame. I think I need to
	// make a Camera object too, but I'm not sure. I need to figure out how the
	// shaders are managed.

	Manager manager(argc, argv);
	manager.get_game()->load();

	ShaderManager sm;
	bool allGood = true;
	allGood &= sm.add_shader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	allGood &= sm.add_shader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	sm.print_shaders();

	string names[] = {"shaders/vertex.glsl", "shaders/fragment.glsl"};
	allGood &= sm.add_shaderProg("test", vector<string>(names, names+sizeof(names) / sizeof(string)));
	cout << "Did everything work? " << (allGood ? "Yup!" : "Nope! :(") << endl;

	sm.print_shaderProgs();

	ShaderProg* sp = sm.get_shaderProg("test");
	cout << "sp = " << sp << endl;
	sp->print_attributes();
	sp->print_uniforms();

	GLuint modelID = sp->get_uniform("model");
	cout << "modelID: " << modelID << endl;

	manager.get_game()->get_renderer()->progID = sp->get_id();
	manager.get_game()->run();
	return 0;
}
