#include "triangle.hpp"

#include "../debug.hpp"

#include <vector>

static constexpr unsigned int k_vertices = 3;

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & color) {

	init(a, b, c, getColorVector(color, k_vertices));

}

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::initializer_list<glm::vec3> & colors) {

	init(a, b, c, getColorVector(colors, k_vertices));

}

void Triangle::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::vector<GLfloat> & colors) {

	m_center = ((a + b) / 2.f + c) / 2.f;

	glBindVertexArray(m_vertexArray);

	bindVertices({
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	});

	bindColors(colors);

	glBindVertexArray(0);

}

void Triangle::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}
