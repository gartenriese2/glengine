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
	// m_windowThreads[windowCounter++] = std::unique_ptr<std::thread>(new std::thread(&Engine::windowThread, width, height, title));
	m_windowThreads[windowCounter++] = std::unique_ptr<WindowThread>(new WindowThread(width, height, title));
	return windowCounter - 1;

}

// void Engine::windowThread(unsigned int width, unsigned int height, const std::string & title) {

// 	Window w(width, height, title);

// }
