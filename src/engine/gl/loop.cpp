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

void Loop::addObjectsToRender(unsigned long renderID, std::set<unsigned long> objectIDs) {
	m_createdRenderings.at(renderID)->addObjects(objectIDs);
}

void Loop::removeObjectFromRender(unsigned long renderID, unsigned long objectID) {
	m_createdRenderings.at(renderID)->removeObject(objectID);
}
