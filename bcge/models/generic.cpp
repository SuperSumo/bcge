#include "generic.h"
#include "../game.h"
#include <iostream>
using namespace std;

GenericObject::GenericObject(Game* game): Object(game)
{}

GenericObject::~GenericObject()
{}

void GenericObject::load()
{}

void GenericObject::unload()
{}
