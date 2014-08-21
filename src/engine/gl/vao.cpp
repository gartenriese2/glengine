#include "vao.hpp"

#include "vbo.hpp"
#include "ibo.hpp"
#include "../debug.hpp"

#include <utility>

namespace gl {

VAO::VAO()
  : gl::Object(GL_VERTEX_ARRAY)
{

	glCreateVertexArrays(1, &m_name);

}

VAO & VAO::operator=(VAO && other) & {

	if (this != &other) {

		if (isValid()) {

			glDeleteVertexArrays(1, &m_name);

		}
		
		std::swap(m_name, other.m_name);

	}

	return *this;

}

VAO::~VAO() {

	glDeleteVertexArrays(1, &m_name);

}

bool VAO::isValid() const {
	return glIsVertexArray(m_name);
}

void VAO::attachVBO(const gl::VBO & vbo, GLuint index, GLuint attribindex) {

	attachBuffer(index, static_cast<GLint>(vbo.getSize()), vbo.getType(), vbo.normalized(),
		0, vbo, static_cast<GLsizei>(vbo.getSize() * vbo.getTypeSize()), attribindex);

}

void VAO::attachIBO(const gl::IBO & ibo) {

	attachIndexBuffer(ibo);

}

void VAO::attachBuffer(GLuint index, GLint size, GLenum type, bool normalized,
	GLuint offset, GLuint buffer, GLsizei stride, GLuint attribindex) {

	if (isValid()) {

		glEnableVertexArrayAttrib(m_name, attribindex);
		glVertexArrayAttribFormat(m_name, index, size, type, normalized, offset);
		glVertexArrayVertexBuffer(m_name, index, buffer, offset, stride);
		glVertexArrayAttribBinding(m_name, attribindex, index);

	}

}

void VAO::attachIndexBuffer(GLuint buffer) {

	if (isValid()) {

		glVertexArrayElementBuffer(m_name, buffer);

	}

}

} // namespace gl
