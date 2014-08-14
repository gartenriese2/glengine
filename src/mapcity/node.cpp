#include "node.hpp"

#include "grid.hpp"

Node::Node(const glm::vec3 & point)
  : m_point(point)
{

}

float Node::getDistance(const Node & other) const {

	return glm::length((other - *this).m_point);

}

const Tile Node::getTile() const {

	return Grid::getTile({m_point[0], m_point[1]});

}
