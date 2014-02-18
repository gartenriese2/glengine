#include "object.hpp"

#include "../debug.hpp"

static const glm::vec3 k_defaultColor {1.f, 0.f, 0.f};

Object::Object()
  : m_modelMatrix(glm::mat4(1.f))
{

	glGenBuffers(1, & m_vertexBuffer);
	glGenBuffers(1, & m_colorBuffer);
	glGenBuffers(1, & m_indexBuffer);
	glGenVertexArrays(1, & m_vertexArray);

}

Object::~Object() {

	glDeleteBuffers(1, & m_vertexBuffer);
	glDeleteBuffers(1, & m_colorBuffer);
	glDeleteBuffers(1, & m_indexBuffer);
	glDeleteVertexArrays(1, & m_vertexArray);

}

void Object::rotate(float radians, const glm::vec3 & axis) {

	m_modelMatrix = glm::translate(m_modelMatrix, m_center);
	m_modelMatrix = glm::rotate(m_modelMatrix, radians, axis);
	m_modelMatrix = glm::translate(m_modelMatrix, -m_center);

}

const std::vector<GLfloat> Object::getColorVector(const std::initializer_list<glm::vec3> & colors, unsigned int maxSize) const {

	std::vector<GLfloat> v;

	for (const auto & color : colors) {
		
		if (&color - colors.begin() >= maxSize) return v;

		v.emplace_back(color.x);
		v.emplace_back(color.y);
		v.emplace_back(color.z);

	}

	for (unsigned int i = v.size() / 3; i < maxSize; ++i) {
		
		v.emplace_back(k_defaultColor[0]);
		v.emplace_back(k_defaultColor[1]);
		v.emplace_back(k_defaultColor[2]);

	}

	return v;

}

const std::vector<GLfloat> Object::getColorVector(const glm::vec3 & color, unsigned int maxSize) const {

	std::vector<GLfloat> v;

	for (unsigned int i = 0; i < maxSize; ++i) {
		
		v.emplace_back(color.x);
		v.emplace_back(color.y);
		v.emplace_back(color.z);

	}

	return v;

}

void Object::bindIndices(const std::vector<GLushort> & v) {
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	bufferData(GL_ELEMENT_ARRAY_BUFFER, v, GL_STATIC_DRAW);

}
