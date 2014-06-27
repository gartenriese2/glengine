#ifndef _PATH_
#define _PATH_

#include "segment.hpp"
#include "../engine/glmincludes.hpp"
#include "../engine/handler.hpp"

#include <vector>

class Path {

	public:

		Path(const std::vector<glm::vec3> &);

		const std::vector<Segment> & getSegments() const { return m_segments; }
		const std::vector<glm::vec3> & getPoints() const { return m_points; }

		bool intersects(const Path &) const;
		const std::vector<Node> getIntersections(const Path &) const;

		ObjectID createObjectID(WindowID &);

		static const Path createPathFromControlPoints(const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);

	private:

		std::vector<Segment> m_segments;
		std::vector<glm::vec3> m_points;

};

#endif // _PATH_
