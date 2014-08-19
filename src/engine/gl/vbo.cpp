#include "vbo.hpp"

namespace gl {

constexpr GLuint k_defaultSize {4};
constexpr GLenum k_defaultType {GL_FLOAT};
constexpr bool k_defaultNormalized {GL_FALSE};

VBO::VBO()
  : m_name{0},
  	m_size{k_defaultSize},
  	m_type{k_defaultType},
  	m_normalized{k_defaultNormalized}
{
	glCreateBuffers(1, &m_name);
}

VBO::VBO(GLuint size, GLenum type, bool normalized)
  : m_name{0},
  	m_size{size},
  	m_type{type},
  	m_normalized{normalized}
{
	glCreateBuffers(1, &m_name);
}

VBO::VBO(const VBO & other)
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

VBO::VBO(VBO && other)
  : m_name{0}
{

	glDeleteBuffers(1, &m_name);
	std::swap(m_name, other.m_name);

}

VBO & VBO::operator=(const VBO & other) & {

	if (this != &other && other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}

	return *this;

}

VBO & VBO::operator=(VBO && other) & {

	if (this != &other) {

		if (isValid()) {
			
			glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
			glDeleteBuffers(1, &m_name);

		}

		std::swap(m_name, other.m_name);

	}

	return *this;

}

VBO::~VBO() {
	
	glNamedBufferData(m_name, 0, nullptr, GL_STREAM_DRAW);
	glDeleteBuffers(1, &m_name);

}

bool VBO::isValid() const {

	return glIsBuffer(m_name);

}

} // namespace gl
