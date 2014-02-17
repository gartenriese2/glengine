#include "engine.hpp"

#include "window.hpp"
#include "debug.hpp"

Engine::Engine() {

	init();

}

Engine::~Engine() {

	for (auto thread : m_windowThreads) {
		// DEB
		thread->join();
		// DEB
	}

	glfwTerminate();

}

void Engine::init() {

	if (!glfwInit()) {
		Debug::log("Could not initialize GLFW!");
		exit(0);
	}

}

void Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	m_windowThreads.emplace_back(new std::thread(&Engine::windowThread, width, height, title));

}

void Engine::windowThread(unsigned int width, unsigned int height, const std::string & title) {

	Window w(width, height, title);

}
