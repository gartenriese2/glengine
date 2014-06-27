#include "path.hpp"

Path::Path(const std::vector<glm::vec3> & nodes)
  : m_points(nodes)
{

	for (unsigned int i = 0; i < nodes.size() - 1; ++i) {

		m_segments.emplace_back(nodes[i], nodes[i + 1]);

	}

}

bool Path::intersects(const Path & other) const {

	for (const auto & seg : m_segments) {
		for (const auto & otherSeg : other.getSegments()) {
			if (seg.intersects(otherSeg)) return true;
		}
	}

	return false;

}

const std::vector<Node> Path::getIntersections(const Path & other) const {

	std::vector<Node> nodes;

	for (const auto & seg : m_segments) {
		for (const auto & otherSeg : other.getSegments()) {
			if (seg.intersects(otherSeg)) {
				nodes.emplace_back(seg.getIntersection(otherSeg));
			}
		}
	}

	return nodes;

}

ObjectID Path::createObjectID(WindowID & win) {

	return win.createSpline(m_points, {0.f, 1.f, 0.f}, 4.f, {0.8f, 0.8f, 0.f});

}


////////////
// STATIC //
////////////


constexpr float k_dist = 0.1f;

const Path Path::createPathFromControlPoints(const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d) {

	float t = 1.f / glm::length(c - b) * k_dist;

	std::vector<glm::vec3> nodes;
	nodes.emplace_back(b);

	for (float f = t; f < 1.f; f += t) {

		glm::vec3 q = 0.5f * ((2.f * b) + (c - a) * f + (2.f * a - 5.f * b + 4.f * c - d) * f * f
			+ (3.f * b - a - 3.f * c + d) * f * f * f);
		nodes.emplace_back(q);

	}

	nodes.emplace_back(c);

	return Path(nodes);

}
