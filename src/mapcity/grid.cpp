#include "grid.hpp"

Grid * Grid::s_instance = nullptr;
std::mutex Grid::s_mutex;

Grid & Grid::instance() {

	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(s_mutex);
	if (s_instance == nullptr) {
		s_instance = new Grid();
	}

	return * s_instance;

}

Grid::Cleanup::~Cleanup() {
	
	std::lock_guard<std::mutex> gaurd(Grid::s_mutex);
	delete Grid::s_instance;
	Grid::s_instance = nullptr;

}

const Tile Grid::getTile(const glm::vec2 & coord) {

	unsigned int x = static_cast<unsigned int>(coord[0] / instance().m_deltaX);
	if (coord[0] < 0.f) --x;
	unsigned int y = static_cast<unsigned int>(coord[1] / instance().m_deltaY);
	if (coord[1] < 0.f) --y;
	return {x, y};

}
