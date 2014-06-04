#include "circle.hpp"

#include "../debug.hpp"

static constexpr unsigned int k_minEdges = 3;
static constexpr unsigned int k_maxEdges = 1000;

Circle::Circle(const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges, const glm::vec3 & color) {

	edges = edges < k_minEdges ? k_minEdges : edges > k_maxEdges ? k_maxEdges : edges;
	init(center, axis, radius, edges, getColorVector(color, edges + 1));

}

Circle::Circle(const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges, const std::initializer_list<glm::vec3> & colors) {

	edges = edges < k_minEdges ? k_minEdges : edges > k_maxEdges ? k_maxEdges : edges;
	init(center, axis, radius, edges, getColorVector(colors, edges + 1));

}

std::shared_ptr<Object> Circle::getCopy() {

	return std::shared_ptr<Object>(new Circle(*this));

}

void Circle::init(const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges, const std::vector<GLfloat> & colors) {

	m_indices = edges + 2;
	setCenter({0.f, 0.f, 0.f});

	std::vector<GLfloat> vertices {0.f, 0.f, 0.f};
	std::vector<GLfloat> normals {0.f, 0.f, 1.f};
	for (unsigned int i = 0; i < edges; ++i) {
		vertices.emplace_back(glm::cos(i * 2*glm::pi<float>() / edges) * radius);
		vertices.emplace_back(glm::sin(i * 2*glm::pi<float>() / edges) * radius);
		vertices.emplace_back(0.f);
		normals.emplace_back(0.f);
		normals.emplace_back(0.f);
		normals.emplace_back(1.f);
	}

	m_vertexBuffer.insertData<GLfloat>(vertices);
	m_vertexBuffer.bindToVAO(m_vertexArray, 0);

	m_colorBuffer.insertData(colors);
	m_colorBuffer.bindToVAO(m_vertexArray, 1);

	m_normalBuffer.insertData<GLfloat>(normals);
	m_normalBuffer.bindToVAO(m_vertexArray, 2);

	std::vector<GLushort> indices;
	for (unsigned int i = 0; i < edges + 1; ++i) {
		indices.emplace_back(i);
	}
	indices.emplace_back(1);
	m_indexBuffer.insertData(indices);
	m_indexBuffer.bindToVAO(m_vertexArray);

	moveTo(center);
	rotate(glm::acos(glm::dot(axis, {0.f, 0.f, 1.f}) / glm::length(axis)), glm::cross(axis, {0.f, 0.f, 1.f}));

	m_data.insert(m_data.begin(), {glm::vec4(center, 0.f), glm::vec4(axis, 0.f), glm::vec4(radius), glm::vec4(edges)});

	for (unsigned int i = 1; i < indices.size() - 1; ++i) {

		glm::vec4 a = glm::vec4(vertices[3 * indices[i]],
			vertices[3 * indices[i] + 1], vertices[3 * indices[i] + 2], 1.f);
		glm::vec4 b = glm::vec4(vertices[0], vertices[1], vertices[2], 1.f);
		glm::vec4 c = glm::vec4(vertices[3 * indices[i + 1]],
			vertices[3 * indices[i + 1] + 1], vertices[3 * indices[i + 1] + 2], 1.f);
		
		m_triangles.emplace_back(a, b, c);

	}

}

void Circle::draw() const {

	glBindVertexArray(m_vertexArray);
	glDrawElements(GL_TRIANGLE_FAN, m_indices * 3, GL_UNSIGNED_SHORT, (void*)0);
	glBindVertexArray(0);

}
