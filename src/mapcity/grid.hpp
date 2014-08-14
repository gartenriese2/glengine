#ifndef _GRID_
#define _GRID_

#include "../engine/glmincludes.hpp"
#include "tile.hpp"

#include <mutex>

class Grid {

	public:

		static const Tile getTile(const glm::vec2 &);

	protected:

		static Grid * s_instance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};

	private:

		Grid() {}
		Grid(const Grid &) = delete;
		Grid(Grid &&) = delete;
		Grid & operator=(const Grid &) = delete;
		Grid & operator=(Grid &&) = delete;
		virtual ~Grid() {}

		static Grid & instance();

		static std::mutex s_mutex;

		float m_deltaX = 100.f;
		float m_deltaY = 100.f;

};

#endif // _GRID_
