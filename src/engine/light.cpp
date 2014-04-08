#include "light.hpp"

Light::Light(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & color)
  : m_pos(pos),
  	m_dir(dir),
	m_color(color),
	m_ambientTerm(0.2f),
	m_shiniess(20.f),
	m_strength(1.f),
	m_attenuation(1.f)
{}

void Light::rotate(float radians, const glm::vec3 & axis) {

	if (glm::length(axis) != 0.f) {

		glm::mat4 rot = glm::rotate(glm::mat4(1.f), radians, axis);
		glm::vec4 tmp = rot * glm::vec4(m_dir, 1.f);
		m_dir = glm::vec3(tmp[0], tmp[1], tmp[2]);

	}

}