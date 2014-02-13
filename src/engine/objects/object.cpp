#include "object.hpp"

Object::Object()
  : m_modelMatrix(glm::mat4(1.f))
{

	glGenBuffers(1, &m_vertexBuffer);
	glGenVertexArrays(1, &m_vertexArray);

}

void Object::rotate(float radians, const glm::vec3 & axis) {

	m_modelMatrix = glm::rotate(m_modelMatrix, radians, axis);

}