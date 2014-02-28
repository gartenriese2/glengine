#ifndef _BUFFER_
#define _BUFFER_

#include "glincludes.hpp"

#include <vector>
#include <iostream>

class Buffer {

	public:

		Buffer();
		Buffer(Buffer &&) = delete;
		Buffer & operator=(const Buffer &) = delete;
		Buffer & operator=(Buffer &&) = delete;
		~Buffer();

		void bind(GLenum = GL_ARRAY_BUFFER);
		void bindToVAO(GLuint, unsigned int);

		template <class T>
		void insertData(const std::vector<T> & data, GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW) {
			bind(target);
			glBufferData(target, data.size() * sizeof(T), &data[0], usage);
		}		

	private:

		GLuint m_name;

};

#endif // _BUFFER_