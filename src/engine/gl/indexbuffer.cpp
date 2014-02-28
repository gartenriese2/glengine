#include "indexbuffer.hpp"

IndexBuffer::IndexBuffer() {

	glGenBuffers(1, &m_name);

}

IndexBuffer::~IndexBuffer() {

	glDeleteBuffers(1, &m_name);

}

void IndexBuffer::bind(GLenum target) {

	glBindBuffer(target, m_name);

}

void IndexBuffer::bindToVAO(GLuint vao) {

	glBindVertexArray(vao);

	bind();
	
	glBindVertexArray(0);

}
