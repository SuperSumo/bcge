#ifndef GENERIC_OBJECT_H_
#define GENERIC_OBJECT_H_

#include "../object.h"

class Game;

class GenericObject: public Object
{
	public:
		GenericObject(Game* game);
		~GenericObject();
		virtual void load();
		virtual void unload();
};

#endif
