#include "window.hpp"

#include <iostream>

Window::Window(unsigned int width, unsigned int height)
  : m_width(width),
  	m_height(height)
{
	init(m_width, m_height, "Title");
}

Window::Window(unsigned int width, unsigned int height, const std::string & title)
  : m_width(width),
  	m_height(height)
{
	init(m_width, m_height, title);
}

Window::~Window() {
	glfwTerminate();
}

void Window::init(unsigned int width, unsigned int height, const std::string & title) {

	if (!glfwInit()) {
		std::cout << "Could not initialize GLFW!\n";
		exit(0);
	}

	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_window) {
        glfwTerminate();
        std::cout << "Could not create Window!\n";
        exit(0);
    }

    glfwMakeContextCurrent(m_window);

    m_loop.start(m_window);

}
