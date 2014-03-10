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

WindowID Engine::createWindow(unsigned int width, unsigned int height, const std::string & title) {

	static WindowID windowCounter = 1;
	WindowID id = windowCounter;
	++windowCounter;

	m_windows[id] = std::shared_ptr<Window>(new Window(width, height, title));
	m_windowThreads[id] = std::unique_ptr<WindowThread>(new WindowThread(m_windows[id]));

	return id;

}

ObjectID Engine::createTriangle(WindowID id, const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & color) {

	return m_objHandler.createObject(m_windows[id]->getLoop(), [=](ObjectID id){
		ObjectInterface::createTriangle(id, a, b, c, color);
	});

}

ObjectID Engine::createTriangle(WindowID id, const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const std::initializer_list<glm::vec3> & colors) {

	return m_objHandler.createObject(m_windows[id]->getLoop(), [=](ObjectID id){
		ObjectInterface::createTriangle(id, a, b, c, colors);
	});

}

ObjectID Engine::createQuadrilateral(WindowID id, const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const glm::vec3 & color) {

	return m_objHandler.createObject(m_windows[id]->getLoop(), [=](ObjectID id){
		ObjectInterface::createQuadrilateral(id, a, b, c, d, color);
	});

}

ObjectID Engine::createQuadrilateral(WindowID id, const glm::vec3 & a, const glm::vec3 & b,
	const glm::vec3 & c, const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	return m_objHandler.createObject(m_windows[id]->getLoop(), [=](ObjectID id){
		ObjectInterface::createQuadrilateral(id, a, b, c, d, colors);
	});

}
