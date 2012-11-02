#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include "instance.h"

class Object;

class Camera: public Instance
{
	public:
		Camera(Object* object,
				glm::vec3 pos=glm::vec3(0,0,0),
				glm::vec3 vel=glm::vec3(0,0,0),
				glm::vec3 acc=glm::vec3(0,0,0),
				glm::vec3 rot=glm::vec3(0,0,0),
				glm::vec3 rotV=glm::vec3(0,0,0),
				glm::vec3 rotA=glm::vec3(0,0,0),
				float fov=60.0f, float nearView=0.1f, float farView=100.0f);

		void change_fov(float delta);
		virtual void draw();
		glm::mat4 get_projection();
		glm::mat4 get_view();

	protected:
		float fov, nearView, farView;
		glm::mat4 projection, view;

	private:
		Camera();
};

#endif /* CAMERA_H_ */
