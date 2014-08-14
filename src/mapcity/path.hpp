#ifndef _PATH_
#define _PATH_

#include "segment.hpp"
#include "../engine/glmincludes.hpp"

#include <vector>

class Path {

	public:

		Path(const std::vector<glm::vec3> &);

		const std::vector<Segment> & getSegments() const { return m_segments; }
		const std::vector<Node> & getNodes() const { return m_nodes; }
		const std::vector<glm::vec3> getPoints() const;

		bool intersects(const Path &) const;
		const std::vector<Node> getIntersections(const Path &) const;

		bool join(const Path &);

		static const Path createPathFromControlPoints(const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		static const Path createPathFromControlPoints(const std::vector<glm::vec3> &);

	private:

		std::vector<Segment> m_segments;
		std::vector<Node> m_nodes;

};

#endif // _PATH_
