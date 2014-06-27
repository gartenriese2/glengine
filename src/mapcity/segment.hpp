#ifndef _SEGMENT_
#define _SEGMENT_

#include "node.hpp"

class Segment {

	public:

		Segment(const Node &, const Node &);

		const Node & getA() const { return m_a; }
		const Node & getB() const { return m_b; }

		float getLength() const;

		bool intersects(const Segment &) const;
		Node getIntersection(const Segment &) const;

	private:

		Segment getShortestConnection(const Segment &) const;
		float getClosestDistance(const Segment &) const;

		Node m_a;
		Node m_b;

};

#endif // _SEGMENT_
