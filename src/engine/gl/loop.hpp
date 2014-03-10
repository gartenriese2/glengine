#ifndef _LOOP_
#define _LOOP_

#include "glincludes.hpp"
#include "../passes/render.hpp"

#include <queue>
#include <memory>
#include <functional>

class Loop {

	public:

		Loop();
		Loop(const Loop &) = delete;
		Loop(Loop &&) = delete;
		Loop & operator=(const Loop &) = delete;
		Loop & operator=(Loop &&) = delete;

		void start(GLFWwindow *);

		void setRendering(const std::shared_ptr<Render> render) { m_rendering = render; }
		void addObjectToRender(unsigned long);
		void addCommand(std::function<void()>);
		void emptyCommands();

	private:

		void render();

		std::shared_ptr<Render> m_rendering;
		std::queue<std::function<void()>> m_commands;

};

#endif // _LOOP_