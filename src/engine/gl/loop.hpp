#ifndef _LOOP_
#define _LOOP_

#include "glincludes.hpp"
#include "../passes/render.hpp"

#include <queue>
#include <memory>
#include <functional>
#include <map>
#include <set>

class Loop {

	public:

		Loop();
		Loop(const Loop &) = delete;
		Loop(Loop &&) = delete;
		Loop & operator=(const Loop &) = delete;
		Loop & operator=(Loop &&) = delete;

		void start(GLFWwindow *);

		void addRendering(unsigned long id, std::shared_ptr<Render> render) { m_createdRenderings.emplace(id, render); }
		const std::shared_ptr<Render> getRendering(unsigned long id) const { return m_createdRenderings.at(id); }
		void setRendering(const std::shared_ptr<Render> render) { m_rendering = render; }
		void addObjectsToRender(unsigned long, std::set<unsigned long>);
		void removeObjectFromRender(unsigned long, unsigned long);
		void addCommand(std::function<void()>);
		void emptyCommands();

	private:

		void render();

		std::shared_ptr<Render> m_rendering;
		std::map<unsigned long, std::shared_ptr<Render>> m_createdRenderings;
		std::queue<std::function<void()>> m_commands;

};

#endif // _LOOP_