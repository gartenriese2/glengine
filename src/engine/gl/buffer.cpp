#include "buffer.hpp"

Buffer::Buffer() {

	glGenBuffers(1, &m_name);

}

Buffer::~Buffer() {

	glDeleteBuffers(1, &m_name);

}

void Buffer::bind(GLenum target) {

	glBindBuffer(target, m_name);

}

void Buffer::bindToVAO(GLuint vao, unsigned int index) {

	glBindVertexArray(vao);

	bind();
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexAttribArray(index);

	glBindVertexArray(0);

}
