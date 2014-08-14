#include "path.hpp"

#include <algorithm>

Path::Path(const std::vector<glm::vec3> & nodes) {

	assert(nodes.size() >= 2);

	for (unsigned int i = 0; i < nodes.size() - 1; ++i) {

		m_segments.emplace_back(nodes[i], nodes[i + 1]);
		m_nodes.emplace_back(nodes[i]);

	}

	m_nodes.emplace_back(nodes.back());

}

const std::vector<glm::vec3> Path::getPoints() const {

	std::vector<glm::vec3> pts;

	for (const auto & node : m_nodes) {
		pts.emplace_back(node);
	}

	return pts;

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

bool Path::join(const Path & path) {

	if (!intersects(path)) return false;

	Node frontThis = m_nodes.front();
	Node frontOther = path.m_nodes.front();
	Node backThis = m_nodes.back();
	Node backOther = path.m_nodes.back();

	if (frontThis == frontOther) {

		m_nodes.insert(m_nodes.begin(), path.m_nodes.end(), path.m_nodes.begin() + 1);
		m_segments.insert(m_segments.begin(), path.m_segments.end(), path.m_segments.begin());

	} else if (frontThis == backOther) {

		m_nodes.insert(m_nodes.begin(), path.m_nodes.begin(), path.m_nodes.end() - 1);
		m_segments.insert(m_segments.begin(), path.m_segments.begin(), path.m_segments.end());

	} else if (backThis == frontOther) {

		m_nodes.insert(m_nodes.end(), path.m_nodes.begin() + 1, path.m_nodes.end());
		m_segments.insert(m_segments.end(), path.m_segments.begin(), path.m_segments.end());
		
	} else if (backThis == backOther) {

		m_nodes.insert(m_nodes.end(), path.m_nodes.end() - 1, path.m_nodes.begin());
		m_segments.insert(m_segments.end(), path.m_segments.end(), path.m_segments.begin());

	} else return false;

	return true;

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

const Path Path::createPathFromControlPoints(const std::vector<glm::vec3> & pts) {

	assert(pts.size() >= 4);

	Path path = createPathFromControlPoints(pts[0], pts[1], pts[2], pts[3]);

	for (unsigned int i = 1; i < pts.size() - 3; ++i) {

		Path tmp = createPathFromControlPoints(pts[i], pts[i + 1], pts[i + 2], pts[i + 3]);
		path.join(tmp);

	}

	return path;

}
