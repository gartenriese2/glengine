#ifndef _NODE_
#define _NODE_

#include "../engine/glmincludes.hpp"
#include "tile.hpp"

constexpr float EPSILON = 0.001f;

class Node {

	public:

		Node(const glm::vec3 &);

		const glm::vec3 & operator()() const { return m_point; }

		operator glm::vec3() const { return m_point; }

		Node & operator+=(const Node & rhs) {
			m_point += rhs.m_point;
			return *this;
		}
		Node & operator-=(const Node & rhs) {
			m_point -= rhs.m_point;
			return *this;
		}
		Node & operator*=(float fac) {
			m_point *= fac;
			return *this;
		}
		Node & operator/=(float fac) {
			m_point /= fac;
			return *this;
		}

		float getDistance(const Node &) const;
		const Tile getTile() const;

	private:

		glm::vec3 m_point;

};

inline bool operator==(const Node & lhs, const Node & rhs) {
	return lhs.getDistance(rhs) < EPSILON;
}
inline bool operator!=(const Node & lhs, const Node & rhs) {
	return !(lhs == rhs);
}

inline Node operator+(Node lhs, const Node & rhs) {
	lhs += rhs;
	return lhs;
}
inline Node operator-(Node lhs, const Node & rhs) {
	lhs -= rhs;
	return lhs;
}
inline Node operator*(Node lhs, float rhs) {
	lhs *= rhs;
	return lhs;
}
inline Node operator*(float lhs, Node rhs) {
	rhs *= lhs;
	return rhs;
}
inline Node operator/(Node lhs, float rhs) {
	lhs /= rhs;
	return lhs;
}
inline Node operator/(float lhs, Node rhs) {
	rhs /= lhs;
	return rhs;
}

#endif // _NODE_
