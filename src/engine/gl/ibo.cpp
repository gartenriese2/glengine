#include "ibo.hpp"

#include <utility>

namespace gl {

IBO::IBO(const IBO & other) {

	if (other.isValid()) {

		GLint size {0};
		glGetNamedBufferParameteriv(other, GL_BUFFER_SIZE, &size);

		glNamedBufferData(m_name, size, nullptr, GL_STATIC_DRAW);
		glCopyNamedBufferSubData(other, m_name, 0, 0, size);

	}
	
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

void IBO::insertData(const std::vector<GLushort> & data) {

	if (isValid()) {
		glNamedBufferData(m_name, static_cast<GLsizeiptr>(data.size() * sizeof(GLushort)), &data[0], GL_STATIC_DRAW);
	}

}

} // namespace gl
