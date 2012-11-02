#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include "vbo.h"
#include <iostream>
#include <algorithm>
#include "utils.h"
using namespace std;

VBO::VBO(): bufSize(0)
{
	id++;
	glGenBuffers(1, &id);
	cout << "VBO::VBO() - creating: " << id << endl;
}
VBO::~VBO()
{
	cout << "VBO::~VBO() - deleting: " << id << endl;
	glDeleteBuffers(1, &id);
}
GLuint VBO::id = 0;

bool VBO::load(float* data, size_t size)
{
	if (size%3)
		error("VBO::load - size is not a multiple of 3!");
	bufSize = size;
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}

void VBO::draw()
{
	if (bufSize)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, bufSize/3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
