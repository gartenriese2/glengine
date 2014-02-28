#ifndef _INDEXBUFFER_
#define _INDEXBUFFER_

#include "glincludes.hpp"
#include "buffer.hpp"

#include <vector>

class IndexBuffer : public Buffer {

	public:

		IndexBuffer();
		IndexBuffer(IndexBuffer &&) = delete;
		IndexBuffer & operator=(const IndexBuffer &) = delete;
		IndexBuffer & operator=(IndexBuffer &&) = delete;
		~IndexBuffer();

		void bind(GLenum = GL_ELEMENT_ARRAY_BUFFER);

		void insertData(const std::vector<GLushort> & data, GLenum target = GL_ELEMENT_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW) {
			bind(target);
			glBufferData(target, data.size() * sizeof(GLushort), &data[0], usage);
		}

		void bindToVAO(GLuint);

	private:

		GLuint m_name;

};

#endif // _INDEXBUFFER_