#include "buffer.hpp"

#include "../debug.hpp"

Buffer::Buffer() {

	glCreateBuffers(1, &m_name);

}

Buffer::Buffer(const Buffer & other) {

	glCreateBuffers(1, &m_name);

	GLint size = 0;
	glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

	glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
	glCopyNamedBufferSubData(other, m_name, 0, 0, size);

}

Buffer::~Buffer() {

	glDeleteBuffers(1, &m_name);

}

GLint Buffer::getSize() {

	GLint size {0};

	glGetNamedBufferParameteriv(m_name, GL_BUFFER_SIZE, &size);

	return size / sizeof(GLfloat) / 3;

}

void Buffer::bind(GLenum target) const {

	glBindBuffer(target, m_name);

}

void Buffer::unbind(GLenum target) const {

	glBindBuffer(target, 0);

}

void Buffer::bindToVAO(GLuint vao, unsigned int index) {

	glBindVertexArray(vao);

	bind();
	// glVertexArrayVertexBuffer(vao, index, m_name, 0, 0);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexArrayAttrib(vao, index);
	unbind();

	glBindVertexArray(0);

}
