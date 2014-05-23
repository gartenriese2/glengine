#include "cuboid.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_vertices = 24;

Cuboid::Cuboid(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
	const glm::vec3 & d, const glm::vec3 & color) {

	init(a, b, c, d, getColorVector(color, k_vertices));

}

Cuboid::Cuboid(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
	const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	init(a, b, c, d, getColorVector(colors, k_vertices));

}

std::shared_ptr<Object> Cuboid::getCopy() {

	return std::shared_ptr<Object>(new Cuboid(*this));

}

void Cuboid::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
	const glm::vec3 & d, const std::vector<GLfloat> & colors) {

	glm::vec3 up = d - a;

	setCenter((b + c + up) / 2.f);

	glm::vec3 e = b + up;
	glm::vec3 f = c + up;
	glm::vec3 g = b + c - a;
	glm::vec3 h = g + up;

	m_vertexBuffer.insertData<GLfloat>({
		a.x, a.y, a.z,
	   	b.x, b.y, b.z,
	   	e.x, e.y, e.z,
	   	d.x, d.y, d.z,

	   	c.x, c.y, c.z,
	   	a.x, a.y, a.z,
	   	d.x, d.y, d.z,
	   	f.x, f.y, f.z,

	   	g.x, g.y, g.z,
	   	c.x, c.y, c.z,
	   	f.x, f.y, f.z,
	   	h.x, h.y, h.z,

	   	b.x, b.y, b.z,
	   	g.x, g.y, g.z,
	   	h.x, h.y, h.z,
	   	e.x, e.y, e.z,

	   	d.x, d.y, d.z,
	   	e.x, e.y, e.z,
	   	h.x, h.y, h.z,
	   	f.x, f.y, f.z,

	   	g.x, g.y, g.z,
	   	c.x, c.y, c.z,
	   	a.x, a.y, a.z,
	   	b.x, b.y, b.z,
	});
	m_vertexBuffer.bindToVAO(m_vertexArray, 0);

	m_colorBuffer.insertData(colors);
	m_colorBuffer.bindToVAO(m_vertexArray, 1);

	glm::vec3 nABED = glm::cross(b - a, d - a);
	glm::vec3 nCADF = glm::cross(a - c, f - c);
	glm::vec3 nGCFH = glm::cross(c - g, h - g);
	glm::vec3 nBGHE = glm::cross(g - b, e - b);
	glm::vec3 nDEHF = glm::cross(e - d, f - d);
	glm::vec3 nGCAB = -glm::cross(c - g, b - g);

	m_normalBuffer.insertData<GLfloat>({
		nABED.x, nABED.y, nABED.z,
		nABED.x, nABED.y, nABED.z,
		nABED.x, nABED.y, nABED.z,
		nABED.x, nABED.y, nABED.z,

		nCADF.x, nCADF.y, nCADF.z,
		nCADF.x, nCADF.y, nCADF.z,
		nCADF.x, nCADF.y, nCADF.z,
		nCADF.x, nCADF.y, nCADF.z,

		nGCFH.x, nGCFH.y, nGCFH.z,
		nGCFH.x, nGCFH.y, nGCFH.z,
		nGCFH.x, nGCFH.y, nGCFH.z,
		nGCFH.x, nGCFH.y, nGCFH.z,

		nBGHE.x, nBGHE.y, nBGHE.z,
		nBGHE.x, nBGHE.y, nBGHE.z,
		nBGHE.x, nBGHE.y, nBGHE.z,
		nBGHE.x, nBGHE.y, nBGHE.z,

		nDEHF.x, nDEHF.y, nDEHF.z,
		nDEHF.x, nDEHF.y, nDEHF.z,
		nDEHF.x, nDEHF.y, nDEHF.z,
		nDEHF.x, nDEHF.y, nDEHF.z,

		nGCAB.x, nGCAB.y, nGCAB.z,
		nGCAB.x, nGCAB.y, nGCAB.z,
		nGCAB.x, nGCAB.y, nGCAB.z,
		nGCAB.x, nGCAB.y, nGCAB.z,
	});
	m_normalBuffer.bindToVAO(m_vertexArray, 2);

	m_indexBuffer.insertData({
		 0,  1,  2,
		 2,  3,  0,

		 4,  5,  6,
		 6,  7,  4,

		 8,  9, 10,
		10, 11,  8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	});
	m_indexBuffer.bindToVAO(m_vertexArray);

	m_data.insert(m_data.begin(), {glm::vec4(a, 0.f), glm::vec4(b, 0.f), glm::vec4(c, 0.f), glm::vec4(d, 0.f)});

}

void Cuboid::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);

}
