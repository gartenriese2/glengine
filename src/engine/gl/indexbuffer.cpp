#include "indexbuffer.hpp"

#include "../debug.hpp"

IndexBuffer::IndexBuffer(const IndexBuffer & other)
  : Buffer()
{

	GLint size = 0;
	glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

	if (size != 0) {
		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);
	}

}

void IndexBuffer::bind(GLenum target) const {

	glBindBuffer(target, m_name);

}

void IndexBuffer::unbind(GLenum target) const {

	glBindBuffer(target, 0);

}

void IndexBuffer::bindToVAO(GLuint vao) {

	glBindVertexArray(vao);
	bind();
	glBindVertexArray(0);
	unbind();

}
