#ifndef _LOOP_
#define _LOOP_

#include "glincludes.hpp"
#include "../passes/render.hpp"

#include <vector>
#include <memory>

class Loop {

	public:

		Loop();
		Loop(const Loop &) = delete;
		Loop(Loop &&) = delete;
		Loop & operator=(const Loop &) = delete;
		Loop & operator=(Loop &&) = delete;

		void start(GLFWwindow *);

		void setRendering(const std::shared_ptr<Render> render) { m_rendering = render; }

	private:

		void render();

		std::shared_ptr<Render> m_rendering;

};

#endif // _LOOP_