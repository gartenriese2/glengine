#include "buffer.hpp"

#include "../debug.hpp"

namespace gl {

Buffer::Buffer()
  : gl::Object(GL_BUFFER)
{

	glCreateBuffers(1, &m_name);

}

Buffer::Buffer(const Buffer & other)
  : gl::Object(GL_BUFFER)
{

	glCreateBuffers(1, &m_name);

}

Buffer::Buffer(Buffer && other)
  : gl::Object(GL_BUFFER)
{

	if (isValid()) {
		
		glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
		glDeleteBuffers(1, &m_name);

	}

	std::swap(m_name, other.m_name);

}

Buffer & Buffer::operator=(const Buffer & other) {

	if (!isValid()) {

		glCreateBuffers(1, &m_name);

	}

	return *this;

};

Buffer & Buffer::operator=(Buffer && other) & {

	if (this != &other) {

		if (isValid()) {
			
			glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
			glDeleteBuffers(1, &m_name);

		}

		std::swap(m_name, other.m_name);

	}

	return *this;

}

Buffer::~Buffer() {

	if (isValid()) {
		
		glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
		glDeleteBuffers(1, &m_name);

	}

}

bool Buffer::isValid() const {

	return glIsBuffer(m_name);

}

GLuint Buffer::getSize() const {

	GLint size {0};

	if (isValid()){
		glGetNamedBufferParameteriv(m_name, GL_BUFFER_SIZE, &size);
	}

	return static_cast<GLuint>(size);

}

}
