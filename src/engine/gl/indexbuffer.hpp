#ifndef _INDEXBUFFER_
#define _INDEXBUFFER_

#include "glincludes.hpp"
#include "buffer.hpp"

#include <vector>

class IndexBuffer : public Buffer {

	public:

		IndexBuffer() {}
		IndexBuffer(const IndexBuffer &);
		IndexBuffer(IndexBuffer &&) = delete;
		IndexBuffer & operator=(const IndexBuffer &) = delete;
		IndexBuffer & operator=(IndexBuffer &&) = delete;
		~IndexBuffer() {}

		void bind(GLenum = GL_ELEMENT_ARRAY_BUFFER) const;
		void unbind(GLenum = GL_ELEMENT_ARRAY_BUFFER) const;

		void insertData(const std::vector<GLushort> & data, GLenum usage = GL_STATIC_DRAW) {
			glNamedBufferData(m_name, data.size() * sizeof(GLushort), &data[0], usage);
		}

		void bindToVAO(GLuint);

};

#endif // _INDEXBUFFER_