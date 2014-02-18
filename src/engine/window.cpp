#include "window.hpp"

#include "debug.hpp"

Window::Window(unsigned int width, unsigned int height, const std::string & title)
  : m_width(width),
	m_height(height)
{
	init(m_width, m_height, title);
}

Window::~Window() {
	glfwDestroyWindow(m_window);
}

void Window::init(unsigned int width, unsigned int height, const std::string & title) {

	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		Debug::log("Could not create Window!");
		exit(0);
	}

	glfwMakeContextCurrent(m_window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		Debug::log("Cound not initialize GLEW!");
		Debug::log(glewGetErrorString(err));
	}

	m_loop.start(m_window);

}
