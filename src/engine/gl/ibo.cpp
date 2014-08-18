#include "ibo.hpp"

#include <utility>

namespace gl {

IBO::IBO()
  : m_name{0}
{
	glCreateBuffers(1, &m_name);
}

IBO::IBO(const IBO & other)
  : m_name{0}
{

	glCreateBuffers(1, &m_name);

	if (other.isValid()) {
		
		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

}

IBO::IBO(IBO && other)
  : m_name{0}
{

	std::swap(m_name, other.m_name);

}

IBO & IBO::operator=(const IBO & other) & {

	if (this != &other && other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

	return *this;

}

IBO & IBO::operator=(IBO && other) & {

	if (this != &other) {

		if (isValid()) {
			glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
		}

		m_name = 0;
		std::swap(m_name, other.m_name);

	}

	return *this;

}

IBO::~IBO() {

	glDeleteBuffers(1, &m_name);

}

bool IBO::isValid() const {

	return glIsBuffer(m_name);

}

GLuint IBO::getSize() const {

	GLint size {0};

	if (isValid()){
		glGetNamedBufferParameteriv(m_name, GL_BUFFER_SIZE, &size);
	}

	return size;

}

void IBO::insertData(const std::vector<GLushort> & data) {

	if (isValid()) {
		glNamedBufferData(m_name, data.size() * sizeof(GLushort), &data[0], GL_STATIC_DRAW);
	}

}

} // namespace gl
