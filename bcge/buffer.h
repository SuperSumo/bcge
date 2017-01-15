#ifndef VBO_H_
#define VBO_H_

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

enum BufferType
{
	VBO,
	CBO,
	IBO
};

class Buffer
{
	public:

		Buffer(BufferType type, GLenum elementType);
		~Buffer();

		template <typename T>
		bool load(T* data, size_t size)
		{
			return _load((GLvoid*)data, size);
		}

		void draw();
		GLuint get_id();

	private:

		GLuint _id;
		BufferType _type;
		GLenum _glType;
		GLenum _elementType;
		size_t _size;

		bool _load(GLvoid* data, size_t size);
};

#endif
