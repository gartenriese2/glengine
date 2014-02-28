#include "object.hpp"

#include "../debug.hpp"

static const glm::vec3 k_defaultColor {1.f, 0.f, 0.f};

Object::Object()
  : m_modelMatrix(glm::mat4(1.f)),
  	m_scaleMatrix(glm::mat4(1.f)),
  	m_rotationMatrix(glm::mat4(1.f)),
  	m_translationMatrix(glm::mat4(1.f))
{

	glGenVertexArrays(1, &m_vertexArray);

}

Object::Object(const Object & other)
  : m_modelMatrix(other.m_modelMatrix),
  	m_scaleMatrix(other.m_scaleMatrix),
  	m_rotationMatrix(other.m_rotationMatrix),
  	m_translationMatrix(other.m_translationMatrix),
  	m_center(other.m_center),
  	m_actualPosition(other.m_actualPosition)
{
Debug::log(m_center);
	
	glGenVertexArrays(1, &m_vertexArray);

	glBindVertexArray(m_vertexArray);

	GLint size = 0;

	// glBindBuffer(GL_COPY_READ_BUFFER, other.m_indexBuffer);
	// glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);Debug::log(size);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	// glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ELEMENT_ARRAY_BUFFER, 0, 0, size);
// Debug::log(size);
// 	glBindBuffer(GL_COPY_READ_BUFFER, other.m_vertexBuffer);
// 	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
// 	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
// 	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
// 	glCopyBufferSubData(other.m_vertexBuffer, m_vertexBuffer, 0, 0, size);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
// 	glEnableVertexAttribArray(0);
// Debug::log(size);
// 	glBindBuffer(GL_COPY_READ_BUFFER, other.m_colorBuffer);
// 	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
// 	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
// 	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
// 	glCopyBufferSubData(other.m_colorBuffer, m_colorBuffer, 0, 0, size);
// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
// 	glEnableVertexAttribArray(1);
Debug::log(size);
	glBindVertexArray(0);

}

Object::~Object() {

	glDeleteVertexArrays(1, & m_vertexArray);

}

void Object::rotate(float radians, const glm::vec3 & axis) {

	if (glm::length(axis) != 0.f) {

		m_rotationMatrix = glm::translate(m_rotationMatrix, m_center);
		m_rotationMatrix = glm::rotate(m_rotationMatrix, radians, axis);
		m_rotationMatrix = glm::translate(m_rotationMatrix, -m_center);
		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;

	}

}

void Object::rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point) {

	if (glm::length(axis) != 0.f) {
		
		rotate(radians, axis);

		// http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html -> Section 6.2
		float x = m_actualPosition.x;
		float y = m_actualPosition.y;
		float z = m_actualPosition.z;
		float a = point.x;
		float b = point.y;
		float c = point.z;
		glm::vec3 nAxis = glm::normalize(axis);
		float u = nAxis.x;
		float v = nAxis.y;
		float w = nAxis.z;

		float retX = (a * (v*v + w*w) - u * (b*v + c*w - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ x * glm::cos(radians) + (-c*v + b*w - w*y + v*z) * glm::sin(radians);
		float retY = (b * (u*u + w*w) - v * (a*u + c*w - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ y * glm::cos(radians) + (c*u - a*w + w*x - u*z) * glm::sin(radians);
		float retZ = (c * (u*u + v*v) - w * (a*u + b*v - u*x - v*y - w*z)) * (1 - glm::cos(radians))
			+ z * glm::cos(radians) + (-b*u + a*v - v*x + u*y) * glm::sin(radians);

		moveTo({retX, retY, retZ});

	}

}

void Object::move(float val, const glm::vec3 & dir) {

	if (glm::length(dir) != 0.f) {

		m_translationMatrix = glm::translate(m_translationMatrix, val * dir);
		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
		m_actualPosition += (val * dir);

	}

}

void Object::moveTo(const glm::vec3 & to) {

	m_translationMatrix = glm::translate(m_translationMatrix, to - m_actualPosition);
	m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	m_actualPosition = to;

}

void Object::setCenter(const glm::vec3 & center) {

	m_center = center;
	m_actualPosition = center;

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
