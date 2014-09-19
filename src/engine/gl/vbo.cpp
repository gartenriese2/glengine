#include "vbo.hpp"

namespace gl {

constexpr GLuint k_defaultChannelSize {4};

VBO::VBO()
  : m_channels{k_defaultChannelSize}
{

}

VBO::VBO(GLuint size)
  : m_channels{size}
{

}

VBO::VBO(const VBO & other)
  : m_channels{other.m_channels}
{

	if (other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

}

VBO::VBO(VBO && other) {

	std::swap(m_channels, other.m_channels);

}

VBO & VBO::operator=(const VBO & other) & {

	if (this != &other && other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

	m_channels = other.m_channels;

	return *this;

}

VBO & VBO::operator=(VBO && other) {

	std::swap(m_channels, other.m_channels);

	return *this;

}

void VBO::insertData(const std::vector<GLfloat> & data, GLenum usage) {
	
	if (isValid()) {
		glNamedBufferData(m_name, static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat)), &data[0], usage);
	}

}

} // namespace gl
