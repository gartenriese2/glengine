#include "triangle.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_vertices = 3;

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & color) {

	init(a, b, c, getColorVector(color, k_vertices));

}

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::initializer_list<glm::vec3> & colors) {

	init(a, b, c, getColorVector(colors, k_vertices));

}

std::shared_ptr<Object> Triangle::getCopy() {

	return std::shared_ptr<Object>(new Triangle(*this));

}

void Triangle::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::vector<GLfloat> & colors) {

	setCenter((a + b + c) / 3.f);

	m_vertexBuffer.insertData<GLfloat>({
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	});
	m_vertexBuffer.bindToVAO(m_vertexArray, 0);

	m_colorBuffer.insertData(colors);
	m_colorBuffer.bindToVAO(m_vertexArray, 1);

	glm::vec3 normal = glm::cross(b - a, c - a);
	m_normalBuffer.insertData<GLfloat>({
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z,
		normal.x, normal.y, normal.z
	});
	m_normalBuffer.bindToVAO(m_vertexArray, 2);

	m_data.insert(m_data.begin(), {glm::vec4(a, 0.f), glm::vec4(b, 0.f), glm::vec4(c, 0.f), glm::vec4(0.f)});

	m_triangles.emplace_back(glm::vec4(a.x, a.y, a.z, 1.f), glm::vec4(b.x, b.y, b.z, 1.f), glm::vec4(c.x, c.y, c.z, 1.f));

}

void Triangle::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}
