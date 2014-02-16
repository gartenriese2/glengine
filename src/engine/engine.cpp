#include "engine.hpp"

#include "window.hpp"
#include "debug.hpp"

Engine::Engine() {

}

Engine::~Engine() {

	for (auto thread : m_windowThreads) {
		// DEB
		thread->join();
		// DEB
	}

}

void Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	m_windowThreads.emplace_back(new std::thread(&Engine::windowThread, width, height, title));

}

void Engine::windowThread(unsigned int width, unsigned int height, const std::string & title) {

	Window w(width, height, title);

}
