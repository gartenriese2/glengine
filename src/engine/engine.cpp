#include "engine.hpp"

#include "window.hpp"
#include "debug.hpp"
#include "objects/objectinterface.hpp"

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

const WindowID Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	std::shared_ptr<Window> ptr(new Window(width, height, title));

	WindowID id(ptr);

	m_windowThreads[id()] = std::unique_ptr<WindowThread>(new WindowThread(ptr));

	return id;

}
