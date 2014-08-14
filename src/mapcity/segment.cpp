#include "segment.hpp"
#include "../engine/debug.hpp"

Segment::Segment(const Node & a, const Node & b)
  : m_a(a),
  	m_b(b)
{

}

float Segment::getLength() const {

	return m_a.getDistance(m_b);

}

bool Segment::intersects(const Segment & other) const {

	if (m_a.getTile() == m_b.getTile() && other.getA().getTile() == other.getB().getTile()
		&& m_a.getTile() != other.getA().getTile()) return false;

	float radiusA = getLength() / 2.f;
	float radiusB = other.getLength() / 2.f;

	Node centerA = (m_a + m_b) / 2.f;
	Node centerB = (other.getA() + other.getB()) / 2.f;

	if (centerA.getDistance(centerB) > radiusA + radiusB + EPSILON) {
		// definitely not intersecting
		return false;
	}

	if (getClosestDistance(other) < EPSILON) return true;

	return false;

}

Segment Segment::getShortestConnection(const Segment & other) const {

	const Node & n0 = getA();
	const Node & n1 = getB();
	const Node & n2 = other.getA();
	const Node & n3 = other.getB();

	float d0232 = glm::dot(n0() - n2(), n3() - n2());
	float d3210 = glm::dot(n3() - n2(), n1() - n0());
	float d3232 = glm::pow(other.getLength(), 2.f);
	float d0210 = glm::dot(n0() - n2(), n1() - n0());
	float d1010 = glm::pow(getLength(), 2.f);

	float d0 = (d0232 * d3210 - d0210 * d3232) / (d1010 * d3232 - d3210 * d3210);
	float d1 = (d0232 + d0 * d3210) / d3232;
	d0 = glm::clamp(d0, 0.f, 1.f);
	d1 = glm::clamp(d1, 0.f, 1.f);

	Node ni0 = n0 + d0 * (n1 - n0);
	Node ni1 = n2 + d1 * (n3 - n2);

	return Segment(ni0, ni1);

}

float Segment::getClosestDistance(const Segment & other) const {

	Segment seg = getShortestConnection(other);

	return seg.getLength();

}

const Node Segment::getIntersection(const Segment & other) const {

	return getShortestConnection(other).getA();

}

float Segment::getDistance(const Node & node) const {

	return glm::length(glm::cross(node() - m_a(), node() - m_b())) / glm::length(m_b() - m_a());

}

const Segment Segment::split(const Node & node) {

	if (getDistance(node) > EPSILON) return {m_a, m_a};

	Segment seg{m_a, node};
	m_a = node;
	return seg;

}
