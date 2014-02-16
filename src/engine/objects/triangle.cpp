#include "triangle.hpp"

#include "../debug.hpp"

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c) {

	init(a, b, c, {1.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {1.f, 0.f, 0.f});

}

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & color) {

	init(a, b, c, color, color, color);

}

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const std::vector<glm::vec3> & colors) {

	glm::vec3 base {1.f, 0.f, 0.f};
	init(a, b, c, colors.size() > 0 ? colors[0] : base, colors.size() > 1 ? colors[1] : base, colors.size() > 2 ? colors[2] : base);

}

void Triangle::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
	const glm::vec3 & colorA, const glm::vec3 & colorB, const glm::vec3 & colorC) {

	m_center = ((a + b) / 2.f + c) / 2.f;

	GLfloat vertexBufferData[] = {
	   a.x, a.y, a.z,
	   b.x, b.y, b.z,
	   c.x, c.y, c.z
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	GLfloat colorBufferData[] = {
		colorA.x, colorA.y, colorA.z,
		colorB.x, colorB.y, colorB.z,
		colorC.x, colorC.y, colorC.z
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

}

void Triangle::draw() const {

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3);
	 
	glDisableVertexAttribArray(0);

}
