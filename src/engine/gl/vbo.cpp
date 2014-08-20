#include "vbo.hpp"

namespace gl {

constexpr GLuint k_defaultSize {4};

VBO::VBO()
  : m_size{k_defaultSize}
{

}

VBO::VBO(GLuint size)
  : m_size{size}
{

}

VBO::VBO(const VBO & other)
  : m_size{other.m_size}
{

	if (other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

}

VBO::VBO(VBO && other) {

	std::swap(m_size, other.m_size);

}

VBO & VBO::operator=(const VBO & other) & {

	if (this != &other && other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

	m_size = other.m_size;

	return *this;

}

VBO & VBO::operator=(VBO && other) {

	std::swap(m_size, other.m_size);

	return *this;

}

void VBO::insertData(const std::vector<GLfloat> & data, GLenum usage) {
	
	if (isValid()) {
		glNamedBufferData(m_name, static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat)), &data[0], usage);
	}

}

} // namespace gl
