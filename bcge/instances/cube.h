#ifndef CUBE_INSTANCE_H_
#define CUBE_INSTANCE_H_

#include "../instance.h"

class Object;

class CubeInstance: public Instance
{
	public:
		CubeInstance(Object* object,
			glm::vec3 pos=glm::vec3(0,0,0),
			glm::vec3 vel=glm::vec3(0,0,0),
			glm::vec3 acc=glm::vec3(0,0,0),
			glm::vec3 rot=glm::vec3(0,0,0),
			glm::vec3 rotV=glm::vec3(0,0,0),
			glm::vec3 rotA=glm::vec3(0,0,0));
		virtual ~CubeInstance();

		virtual void draw();
};

#endif
