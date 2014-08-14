#ifndef _BUFFER_
#define _BUFFER_

#include "glincludes.hpp"

#include <vector>
#include <iostream>

class Buffer {

	public:

		Buffer();
		Buffer(const Buffer &);
		Buffer(Buffer &&) = delete;
		Buffer & operator=(const Buffer &) = delete;
		Buffer & operator=(Buffer &&) = delete;
		~Buffer();

		operator GLuint() const { return m_name; }

		GLint getSize();

		void bind(GLenum = GL_ARRAY_BUFFER) const;
		void unbind(GLenum = GL_ARRAY_BUFFER) const;
		void bindToVAO(GLuint, unsigned int);

		template <class T>
		void insertData(const std::vector<T> & data, GLenum usage = GL_STATIC_DRAW) {
			glNamedBufferData(m_name, data.size() * sizeof(T), &data[0], usage);
		}		

	protected:

		GLuint m_name;

};

#endif // _BUFFER_