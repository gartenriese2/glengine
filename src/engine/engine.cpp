#include "engine.hpp"

#include "window.hpp"
#include "debug.hpp"

Engine::Engine() {

	init();

}

Engine::~Engine() {

	for (auto & thread : m_windowThreads) {
		thread.second.reset(nullptr);
	}

	glfwTerminate();

}

void Engine::init() {

	if (!glfwInit()) {
		Debug::log("Could not initialize GLFW!");
		exit(0);
	}

}

WindowID Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	static WindowID windowCounter = 0;
	std::shared_ptr<Window> ptr;
	m_windowThreads[windowCounter++] = std::unique_ptr<WindowThread>(new WindowThread(ptr, width, height, title));
	Loop & l = ptr->getLoop();
	return windowCounter - 1;

}
