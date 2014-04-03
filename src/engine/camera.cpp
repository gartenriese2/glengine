#include "camera.hpp"

#include "debug.hpp"

#include <utility>

Camera::Camera(const glm::vec3 & pos, const glm::vec3 & dir, const glm::vec3 & up, float fov,
	int width, int height, float near, float far)
  : m_width(width),
  	m_height(height),
  	m_fov(fov),
  	m_pos(pos),
  	m_dir(glm::normalize(dir)),
  	m_up(glm::normalize(up)),
  	m_initPos(pos),
  	m_initDir(m_dir),
  	m_initUp(m_up)
{

	calculateView();
	m_proj = glm::perspective(m_fov, static_cast<float>(width) / static_cast<float>(height), near, far);

}

void Camera::calculateView() {

	m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);

}

// Camera::Camera(const glm::vec3 & pos, const glm::vec3 & look, const glm::vec3 & up, float left, float right, float top, float bottom) {

// m_pos = pos;
// m_dir = glm::normalize(look);
// m_up = glm::normalize(up);

// m_view = glm::lookAt(m_pos, m_pos + m_dir, m_up);
// m_proj = glm::ortho(left, right, bottom, top);

// m_initPos = m_pos;
// m_initDir = m_dir;
// m_initUp = m_up;

// }

void Camera::reset() {

	m_pos = m_initPos;
	m_dir = m_initDir;
	m_up = m_initUp;

	calculateView();

}

void Camera::move(const glm::vec3 & change) {

	m_pos += change;

	calculateView();

}

void Camera::moveTo(const glm::vec3 & to) {

	m_pos = to;

	calculateView();

}

void Camera::rotate(float radians, const glm::vec3 & axis) {

	// TO DO

}

void Camera::rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point) {

	// TO DO

}