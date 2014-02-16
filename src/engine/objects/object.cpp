#include "object.hpp"

#include "../debug.hpp"

Object::Object()
  : m_modelMatrix(glm::mat4(1.f))
{

	glGenBuffers(1, & m_vertexBuffer);
	glGenBuffers(1, & m_colorBuffer);
	glGenVertexArrays(1, & m_vertexArray);

}

void Object::rotate(float radians, const glm::vec3 & axis) {

	m_modelMatrix = glm::translate(m_modelMatrix, m_center);
	m_modelMatrix = glm::rotate(m_modelMatrix, radians, axis);
	m_modelMatrix = glm::translate(m_modelMatrix, -m_center);

}