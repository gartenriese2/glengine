#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../debug.hpp"
#include "../passes/basicrender.hpp"
#include "../handler.hpp"

#include <mutex>

static std::mutex s_mutex;

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) {

	BasicRender r(Camera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f}, 45.f, 1000, 800, 0.1f, 10.f));
	setRendering(std::shared_ptr<Render>(&r));

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		emptyCommands();

		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

}

void Loop::render() {

	if (m_rendering) {
		m_rendering->draw();
	}

}

void Loop::addCommand(std::function<void()> func) {

	std::lock_guard<std::mutex> lock(s_mutex);

	m_commands.push(func);

}

void Loop::emptyCommands() {

	std::lock_guard<std::mutex> lock(s_mutex);

	while (!m_commands.empty()) {
		m_commands.front()();
		m_commands.pop();
	}

}

void Loop::addObjectToRender(unsigned long id) {
	m_rendering->addObjects({id});
}

void Loop::removeObjectFromRender(unsigned long id) {
	m_rendering->removeObject({id});
}
