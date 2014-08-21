#include "globject.hpp"

namespace gl {

Object::Object(GLenum identifier)
  : m_name{0},
  	m_identifier{identifier}
{

}

Object::Object(const Object & other)
  : m_name{0},
    m_identifier{other.m_identifier}
{

}

Object::Object(Object && other)
  : m_name{0},
  	m_identifier{GL_NONE}
{
	std::swap(m_name, other.m_name);
	std::swap(m_identifier, other.m_identifier);
}

void Object::setLabel(const std::string & name) {
	
	const std::string str = name.substr(0, GL_MAX_LABEL_LENGTH);
	glObjectLabel(m_identifier, m_name, static_cast<GLsizei>(str.size()), str.c_str());

}

const std::string Object::getLabel() const {

	const unsigned int size {GL_MAX_LABEL_LENGTH};
	char label[size];
	GLsizei len[size];
	glGetObjectLabel(m_identifier, m_name, size, len, label);

	return label;

}

} // namespace gl
