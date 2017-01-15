#include <iostream>
#include <algorithm>

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

#include "buffer.h"
#include "utils.h"

using namespace std;

Buffer::Buffer(BufferType type, GLenum elementType):
	_id(-1), _type(type), _elementType(elementType), _size(0)
{
	glGenBuffers(1, &_id);
	switch (_type)
	{
		case VBO:
		case CBO:
			_glType = GL_ARRAY_BUFFER;
			break;

		case IBO:
			_glType = GL_ELEMENT_ARRAY_BUFFER;
			break;
	}
//	cout << "Buffer::Buffer() - creating: " << id << endl;
}
Buffer::~Buffer()
{
//	cout << "Buffer::~Buffer() - deleting: " << id << endl;
	glDeleteBuffers(1, &_id);
}

bool Buffer::_load(GLvoid* data, size_t size)
{
	if (((_type == VBO) && (size%3)) || ((_type == CBO) && (size%4)))
	{
		cerr << "Buffer::load - wrong size for the type of buffer!" << endl;
		return false;
	}
	_size = size;
	glBindBuffer(_glType, _id);
	glBufferData(_glType, _size, data, GL_STATIC_DRAW);
	if (_type == VBO)
		glVertexPointer(3, _elementType, 0, 0);
	else if (_type == CBO)
		glColorPointer(4, _elementType, 0, 0);
	glBindBuffer(_glType, 0);
	return true;
}

void Buffer::draw()
{
	if (_size)
	{
		glBindBuffer(_glType, _id);
		if (_type == VBO)
			glDrawArrays(GL_TRIANGLES, 0, _size/3);
			// glDrawArrays(GL_POINTS, 0, _size/3);
		if (_type == IBO)
			glDrawElements(GL_TRIANGLES, _size/sizeof(_elementType), \
				_elementType, 0);
		glBindBuffer(_glType, 0);
	}
}

GLuint Buffer::get_id()
{
	return _id;
}
