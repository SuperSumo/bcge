#ifndef CUBE_OBJECT_H_
#define CUBE_OBJECT_H_

#include "../object.h"

class Game;

class CubeObject: public Object
{
	public:
		CubeObject(Game* game);
		~CubeObject();
		virtual void load();
		virtual void unload();
};

#endif
