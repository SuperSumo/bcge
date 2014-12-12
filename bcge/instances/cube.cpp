#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../object.h"
#include "../game.h"
#include "../renderer.h"
#include "cube.h"

CubeInstance::CubeInstance(Object* object,
				glm::vec3 pos,
				glm::vec3 vel,
				glm::vec3 acc,
				glm::vec3 rot,
				glm::vec3 rotV,
				glm::vec3 rotA):
				Instance(object, pos, vel, acc, rot, rotV, rotA)
{}

CubeInstance::~CubeInstance()
{}

void CubeInstance::draw()
{
	// Create the model matrix
	glm::mat4 modelTrans = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 modelRotZ = glm::rotate(modelTrans, rot.z, glm::vec3(0.0f, 0.0f, -1.0f));
	glm::mat4 modelRotY = glm::rotate(modelRotZ, rot.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::rotate(modelRotY, rot.x, glm::vec3(0.0f, 1.0f, 0.0f));

	// Grab the current program's ID
	GLuint progID = object->get_progID();

	// Update shader info
	GLuint modelID = glGetUniformLocation(progID, "model");
	glUniformMatrix4fv(modelID, 1, false, glm::value_ptr(model));

	// Draw from the object's vbo
	object->draw();
}
