#include "engine.hpp"

#include "window.hpp"

Engine::Engine() {

}

Engine::~Engine() {

	m_rendering->join();

}

void Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	m_rendering = new std::thread(&Engine::windowThread, width, height, title);

}

void Engine::windowThread(unsigned int width, unsigned int height, const std::string & title) {

	Window w(width, height, title);

}
