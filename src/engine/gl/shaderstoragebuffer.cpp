#include "shaderstoragebuffer.hpp"

ShaderStorageBuffer::ShaderStorageBuffer() {

	glGenBuffers(1, &m_name);

}

ShaderStorageBuffer::~ShaderStorageBuffer() {

	glDeleteBuffers(1, &m_name);

}

void ShaderStorageBuffer::bindTo(unsigned int to) {

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_name);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, to, m_name);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}
