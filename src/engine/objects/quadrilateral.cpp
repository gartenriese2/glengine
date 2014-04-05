#include "quadrilateral.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_vertices = 4;

Quadrilateral::Quadrilateral(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d,
	const glm::vec3 & color) {

	init(a, b, c, d, getColorVector(color, k_vertices));

}

Quadrilateral::Quadrilateral(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d,
	const std::initializer_list<glm::vec3> & colors) {

	init(a, b, c, d, getColorVector(colors, k_vertices));

}

std::shared_ptr<Object> Quadrilateral::getCopy() {

	return std::shared_ptr<Object>(new Quadrilateral(*this));

}

void Quadrilateral::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d,
	const std::vector<GLfloat> & colors) {

	setCenter((a + b + c + d) / 4.f);

	m_vertexBuffer.insertData<GLfloat>({
		a.x, a.y, a.z,
	   	b.x, b.y, b.z,
	   	c.x, c.y, c.z,
	   	d.x, d.y, d.z
	});
	m_vertexBuffer.bindToVAO(m_vertexArray, 0);

	m_colorBuffer.insertData(colors);
	m_colorBuffer.bindToVAO(m_vertexArray, 1);

	glm::vec3 nA = glm::cross(b - a, d - a);
	glm::vec3 nB = glm::cross(c - b, a - b);
	glm::vec3 nC = glm::cross(d - c, b - c);
	glm::vec3 nD = glm::cross(a - d, c - d);
	m_normalBuffer.insertData<GLfloat>({
		nA.x, nA.y, nA.z,
		nB.x, nB.y, nB.z,
		nC.x, nC.y, nC.z,
		nD.x, nD.y, nD.z
	});
	m_normalBuffer.bindToVAO(m_vertexArray, 2);

	m_indexBuffer.insertData({
		0, 1, 2,
		2, 3, 0
	});
	m_indexBuffer.bindToVAO(m_vertexArray);

}

void Quadrilateral::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);

}
