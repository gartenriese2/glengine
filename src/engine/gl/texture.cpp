#include "texture.hpp"

#include "../debug.hpp"
#include "fbo.hpp"

Texture::Texture(unsigned int width, unsigned int height, GLenum format)
  : m_width{width},
  	m_height{height},
  	m_format{format}
{

	glCreateTextures(m_target, 1, &m_name);
	glTextureStorage2D(m_name, 1, m_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

}

Texture::~Texture() {

	glDeleteTextures(1, &m_name);

}

void Texture::resize(unsigned int width, unsigned int height) {

	m_width = width;
	m_height = height;

	glDeleteTextures(1, &m_name);
	glCreateTextures(m_target, 1, &m_name);
	glTextureStorage2D(m_name, 1, m_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

}
