#include "spline.hpp"

#include "../debug.hpp"

static constexpr float k_minWidth = 0.1f;

Spline::Spline(const glm::vec3 & start, const glm::vec3 & dirStart, const glm::vec3 & end,
	const glm::vec3 & dirEnd, const glm::vec3 & up, float widthStart, float widthEnd, unsigned int steps,
	const glm::vec3 & color) {

	if (steps < 2) steps = 2;
	if (widthStart < k_minWidth) widthStart = k_minWidth;
	if (widthEnd < k_minWidth) widthEnd = k_minWidth;

	float smoothness = glm::length(end - start) / 10.f / ((glm::length(dirStart) + glm::length(dirEnd)) / 2.f);

	std::vector<glm::vec3> path;
	for (unsigned int i = 0; i < steps; ++i) {

		float s = static_cast<float>(i) / static_cast<float>(steps - 1);
		float h1 = 2 * glm::pow(s, 3.f) - 3 * glm::pow(s, 2.f) + 1.f;
		float h2 = -2 * glm::pow(s, 3.f) + 3 * glm::pow(s, 2.f);
		float h3 = glm::pow(s, 3.f) - 2 * glm::pow(s, 2.f) + s;
		float h4 = glm::pow(s, 3.f) - glm::pow(s, 2.f);
		glm::vec3 p = h1 * start * smoothness + h2 * end * smoothness + h3 * dirStart + h4 * dirEnd;
		path.emplace_back(p / smoothness);

	}

	std::vector<glm::vec3> tangents;
	tangents.emplace_back(glm::normalize(dirStart));
	for (unsigned int i = 1; i < steps - 1; ++i) {
		tangents.emplace_back(glm::normalize(path[i + 1] - path[i - 1]));
	}
	tangents.emplace_back(glm::normalize(dirEnd));

	std::vector<glm::vec3> vertices;
	for (unsigned int i = 0; i < steps; ++i) {
		float w = widthStart + (widthEnd - widthStart) * static_cast<float>(i) / static_cast<float>(steps - 1);
		vertices.emplace_back(path[i] - w * glm::normalize(glm::cross(tangents[i], up)));
		vertices.emplace_back(path[i] + w * glm::normalize(glm::cross(tangents[i], up)));
	}

	init(vertices, up, color);

}

std::shared_ptr<Object> Spline::getCopy() {

	return std::shared_ptr<Object>(new Spline(*this));

}

void Spline::init(const std::vector<glm::vec3> & vert, const glm::vec3 & up, const glm::vec3 & color) {

	m_indices = vert.size();
	setCenter((vert[0] + vert[1] + vert[m_indices - 2] + vert[m_indices - 1]) / 4.f);

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> colors;
	for (unsigned int i = 0; i < m_indices; ++i) {
		vertices.emplace_back(vert[i][0]);
		vertices.emplace_back(vert[i][1]);
		vertices.emplace_back(vert[i][2]);
		normals.emplace_back(up[0]);
		normals.emplace_back(up[1]);
		normals.emplace_back(up[2]);
		colors.emplace_back(color[0]);
		colors.emplace_back(color[1]);
		colors.emplace_back(color[2]);
	}

	m_vertexBuffer.insertData<GLfloat>(vertices);
	m_vertexBuffer.bindToVAO(m_vertexArray, 0);

	m_colorBuffer.insertData(colors);
	m_colorBuffer.bindToVAO(m_vertexArray, 1);

	m_normalBuffer.insertData<GLfloat>(normals);
	m_normalBuffer.bindToVAO(m_vertexArray, 2);

	std::vector<GLushort> indices;
	for (unsigned int i = 0; i < m_indices; ++i) {
		indices.emplace_back(i);
	}
	
	m_indexBuffer.insertData(indices);
	m_indexBuffer.bindToVAO(m_vertexArray);

}

void Spline::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);

}