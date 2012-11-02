#include "instance.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "object.h"

Instance::Instance(Object* object,
		glm::vec3 pos, glm::vec3 vel, glm::vec3 acc,
		glm::vec3 rot, glm::vec3 rotV, glm::vec3 rotA):
		object(object),
		pos(pos), vel(vel), acc(acc),
		rot(rot), rotV(rotV), rotA(rotA),
		model(glm::mat4(1.0f))
{}

Instance::~Instance()
{}

void Instance::update(float dt)
{
	pos += (vel += 0.5f*acc*dt*dt)*dt;
	rot += (rotV += 0.5f*rotA*dt*dt)*dt;
}
