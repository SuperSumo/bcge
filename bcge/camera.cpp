#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "game.h"
#include "defines.h"
#include "manager.h"
#include "window.h"
#include "instance.h"
#include "object.h"
#include "renderer.h"
#include "utils.h"
#include <iostream>
using namespace std;

Camera::Camera(Object* object,
				glm::vec3 pos,
				glm::vec3 vel,
				glm::vec3 acc,
				glm::vec3 rot,
				glm::vec3 rotV,
				glm::vec3 rotA,
				float fov, float nearView, float farView):
				Instance(object, pos, vel, acc, rot, rotV, rotA),
				fov(fov), nearView(nearView), farView(farView),
				projection(glm::mat4(1.0f)),
				view(glm::mat4(1.0f))
{}

void Camera::change_fov(float delta)
{
	fov += delta;
}

void Camera::draw()
{
	uint w = object->get_game()->get_manager()->get_window()->width();
	uint h = object->get_game()->get_manager()->get_window()->height();
//	GLuint progID = object->get_game()->get_renderer()->progID;

	// Set up the projection and view matrices
	projection = glm::perspective(fov, float(w)/h, nearView, farView);
	glm::mat4 viewTrans = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 viewRotY = glm::rotate(viewTrans, rot.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	view = glm::rotate(viewRotY, rot.x, glm::vec3(0.0f, 1.0f, 0.0f));

//	cout << display_matrix(projection*view) << endl;
}

void Camera::apply_to_shader(GLuint progID)
{
	// Apply the projection and view matrices into the shader
	GLuint viewID = glGetUniformLocation(progID, "view");
	GLuint projectionID = glGetUniformLocation(progID, "projection");
	glUniformMatrix4fv(viewID, 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(projectionID, 1, false, glm::value_ptr(projection));
}

glm::mat4 Camera::get_projection()
{
	return projection;
}

glm::mat4 Camera::get_view()
{
	return view;
}
