#include "vao.hpp"

#include "vbo.hpp"
#include "ibo.hpp"

#include <utility>

namespace gl {

VAO::VAO()
  : m_name{0}
{

	glCreateVertexArrays(1, &m_name);

}

VAO::VAO(VAO && other)
  : m_name{0}
{
	std::swap(m_name, other.m_name);
}

VAO & VAO::operator=(VAO && other) & {

	if (this != &other) {

		glDeleteVertexArrays(1, &m_name);
		std::swap(m_name, other.m_name);

	}

	return *this;

}

VAO::~VAO() {

	glDeleteVertexArrays(1, &m_name);

}

const std::string VAO::getLabel() const {

	const unsigned int size {64};
	char label[size];
	GLsizei len[size];
	glGetObjectLabel(GL_VERTEX_ARRAY, m_name, size, len, label);

	return label;

}

void VAO::setLabel(const std::string & name) {
	
	glObjectLabel(GL_VERTEX_ARRAY, m_name, name.size(), name.c_str());

}

void VAO::attachVBO(const gl::VBO & vbo, GLuint index, GLuint attribindex) {

	attachBuffer(index, vbo.getSize(), vbo.getType(), vbo.normalized(), 0, vbo, 0, attribindex);

}

void VAO::attachIBO(const gl::IBO & ibo) {

	attachIndexBuffer(ibo);

}

void VAO::attachBuffer(GLuint index, GLint size, GLenum type, bool normalized,
	GLuint offset, GLuint buffer, GLsizei stride, GLuint attribindex) {

	glVertexArrayAttribFormat(m_name, index, size, type, normalized, offset);
	glVertexArrayVertexBuffer(m_name, index, buffer, offset, stride);
	glVertexArrayAttribBinding(m_name, attribindex, index);

}

void VAO::attachIndexBuffer(GLuint buffer) {

	glVertexArrayElementBuffer(m_name, buffer);

}

} // namespace gl
