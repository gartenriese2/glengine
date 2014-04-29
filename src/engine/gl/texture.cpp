#include "texture.hpp"

#include "../debug.hpp"
#include "fbo.hpp"

Texture::Texture(unsigned int width, unsigned int height, GLenum format)
  : m_width(width),
  	m_height(height),
  	m_format(format)
{

	glGenTextures(1, &m_name);

	bind();
	glTexStorage2D(m_target, 1, m_format, m_width, m_height);
	unbind();

}

Texture::~Texture() {

	glDeleteTextures(1, &m_name);

}

void Texture::bind() const {

	glBindTexture(m_target, m_name);

}

void Texture::unbind() const {

	glBindTexture(m_target, 0);

}

void Texture::resize(unsigned int width, unsigned int height) {

	m_width = width;
	m_height = height;

	glDeleteTextures(1, &m_name);
	glGenTextures(1, &m_name);

	bind();
	glTexStorage2D(m_target, 1, m_format, m_width, m_height);
	unbind();

}
