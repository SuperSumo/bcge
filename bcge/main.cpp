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
	Manager manager(argc, argv);
	manager.get_game()->load();
	manager.get_game()->run();
	return 0;
}
