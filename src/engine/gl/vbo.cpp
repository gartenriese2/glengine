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

VBO::~VBO() {
	glDeleteBuffers(1, &m_name);
}

} // namespace gl
