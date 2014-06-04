#ifndef _ROAD_
#define _ROAD_

#include <vector>

#include "../engine/glmincludes.hpp"
#include "../engine/handler.hpp"

class Road {

	public:

		Road(const std::vector<glm::vec2> &, WindowID &, RenderID &);

	private:

		std::vector<glm::vec2> m_points;
		std::vector<glm::vec2> m_directions;
		std::vector<ObjectID> m_objects;

};

#endif // _ROAD_