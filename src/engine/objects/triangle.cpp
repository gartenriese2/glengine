#include "triangle.hpp"

Triangle::Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c) {

	GLfloat vertexBufferData[] = {
	   a.x, a.y, a.z,
	   b.x, b.y, b.z,
	   c.x, c.y, c.z
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

}

void Triangle::draw() const {

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	 
	glDisableVertexAttribArray(0);

}
