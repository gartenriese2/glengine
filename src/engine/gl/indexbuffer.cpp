#include "indexbuffer.hpp"

#include "../debug.hpp"

IndexBuffer::IndexBuffer(const IndexBuffer & other)
  : Buffer()
{

	other.bind(GL_COPY_READ_BUFFER);
	bind(GL_COPY_WRITE_BUFFER);

	GLint size = 0;
	GLint size2 = 0;
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
	Debug::log("GL_COPY_READ_BUFFER " + std::to_string(size));

Debug::logGL();
glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_SIZE, &size2);
Debug::log("GL_COPY_WRITE_BUFFER " + std::to_string(size2));
Debug::logGL();

	if (size != 0) {
		glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);

glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_SIZE, &size2);
Debug::log("GL_COPY_WRITE_BUFFER " + std::to_string(size2));

		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
	}


	other.unbind(GL_COPY_READ_BUFFER);
	unbind(GL_COPY_WRITE_BUFFER);

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
	unbind();
	
	glBindVertexArray(0);

}
