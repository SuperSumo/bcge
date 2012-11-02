#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include "buffer.h"
#include <iostream>
#include <algorithm>
#include "utils.h"
using namespace std;

Buffer::Buffer(BufferType type, GLenum elementType):
		id(-1), type(type), elementType(elementType), size(0)
{
	glGenBuffers(1, &id);
	switch (type)
	{
		case vbo:
		case cbo:
			glType = GL_ARRAY_BUFFER;
			break;
		case ibo:
			glType = GL_ELEMENT_ARRAY_BUFFER;
			break;
	}
//	cout << "Buffer::Buffer() - creating: " << id << endl;
}
Buffer::~Buffer()
{
//	cout << "Buffer::~Buffer() - deleting: " << id << endl;
	glDeleteBuffers(1, &id);
}

bool Buffer::load(GLfloat* data, size_t size)
{
	return _load((GLvoid*)data, size);
}

bool Buffer::load(GLuint* data, size_t size)
{
	return _load((GLvoid*)data, size);
}

bool Buffer::_load(GLvoid* data, size_t size)
{
	if (((type == vbo) && (size%3)) || ((type == cbo) && (size%4)))
	{
		error("Buffer::load - size is not correct for the type of buffer!");
		return false;
	}
	Buffer::size = size;
	glBindBuffer(glType, id);
	glBufferData(glType, size, data, GL_STATIC_DRAW);
	if (type == vbo)
		glVertexPointer(3, elementType, 0, 0);
	else if (type == cbo)
		glColorPointer(4, elementType, 0, 0);
	glBindBuffer(glType, 0);
	return true;
}

void Buffer::draw()
{
	if (size)
	{
		glBindBuffer(glType, id);
		if (type == vbo)
			glDrawArrays(GL_TRIANGLES, 0, size/3);
		if (type == ibo)
			glDrawElements(GL_TRIANGLES, size/sizeof(elementType),\
					elementType, 0);
		glBindBuffer(glType, 0);
	}
}

GLuint Buffer::get_id()
{
	return id;
}
