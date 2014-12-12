#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <glm/glm.hpp>

class Object;

class Instance
{
	public:
		Instance(Object* object,
			glm::vec3 pos=glm::vec3(0,0,0),
			glm::vec3 vel=glm::vec3(0,0,0),
			glm::vec3 acc=glm::vec3(0,0,0),
			glm::vec3 rot=glm::vec3(0,0,0),
			glm::vec3 rotV=glm::vec3(0,0,0),
			glm::vec3 rotA=glm::vec3(0,0,0));
		virtual ~Instance();

		virtual void update(float dt);
		virtual void draw()=0;

		glm::vec3 pos, vel, acc;
		glm::vec3 rot, rotV, rotA;
		glm::mat4 model;

	protected:
		// Position, rotation, velocity, acceleration
		Object* object;

};

#endif
