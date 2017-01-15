#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "buffer.h"
#include "utils.h"

Buffer::Buffer(BufferType type, GLenum elementType):
	_id(-1), _type(type), _elementType(elementType), _size(0)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Buffer::Buffer()");
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
}
Buffer::~Buffer()
{
	glDeleteBuffers(1, &_id);
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Buffer::~Buffer()");
}

bool Buffer::_load(GLvoid* data, size_t size)
{
	if (((_type == VBO) && (size%3)) || ((_type == CBO) && (size%4)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER,
			"Buffer::_load() - wrong size for the type of buffer");
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
