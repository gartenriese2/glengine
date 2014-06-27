#include "node.hpp"

Node::Node(const glm::vec3 & point)
  : m_point(point)
{

}

float Node::getDistance(const Node & other) const {

	return glm::length((other - m_point).m_point);

}
