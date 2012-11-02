#ifndef VBO_H_
#define VBO_H_

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>

class Buffer
{
	public:

		enum BufferType
		{
			vbo,
			cbo,
			ibo
		};

		Buffer(BufferType type, GLenum elementType);
		~Buffer();
		bool load(GLfloat* data, size_t size);
		bool load(GLuint* data, size_t size);
		void draw();
		GLuint get_id();

	private:

		GLuint id;
		BufferType type;
		GLenum glType, elementType;
		size_t size;

		bool _load(GLvoid* data, size_t size);
};

#endif
