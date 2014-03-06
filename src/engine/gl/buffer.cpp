#include "buffer.hpp"

#include "../debug.hpp"

Buffer::Buffer() {

	glGenBuffers(1, &m_name);

}

Buffer::Buffer(const Buffer & other) {

	glGenBuffers(1, &m_name);

	other.bind(GL_COPY_READ_BUFFER);
	bind(GL_COPY_WRITE_BUFFER);

	GLint size = 0;
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);

	glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

	other.unbind(GL_COPY_READ_BUFFER);
	unbind(GL_COPY_WRITE_BUFFER);

}

Buffer::~Buffer() {

	glDeleteBuffers(1, &m_name);

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
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	glEnableVertexAttribArray(index);
	unbind();

	glBindVertexArray(0);

}
