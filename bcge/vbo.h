#ifndef VBO_H_
#define VBO_H_

#include <SFML/OpenGL.hpp>

class VBO
{
	public:

		VBO();
		~VBO();
		bool load(float* data, size_t size);
		void draw();

	private:

		static GLuint id;
		size_t bufSize;
};

#endif
