#include "object.hpp"

Object::Object() {

	glGenBuffers(1, &m_vertexBuffer);
	glGenVertexArrays(1, &m_vertexArray);

}