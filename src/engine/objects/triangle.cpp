#include "triangle.hpp"

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c) {

	init(a, b, c, {1.f, 0.f, 0.f});

}

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & color) {

	init(a, b, c, color);

}

void Triangle::init(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & color) {

	GLfloat vertexBufferData[] = {
	   a.x, a.y, a.z,
	   b.x, b.y, b.z,
	   c.x, c.y, c.z
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	GLfloat colorBufferData[] = {
		color.x, color.y, color.z,
		color.x, color.y, color.z,
		color.x, color.y, color.z
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
