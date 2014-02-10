#ifndef _WINDOW_
#define _WINDOW_

#include "../includes/glew.h"
#include "../includes/glfw3.h"

#include "loop.hpp"

#include <string>
#include <thread>

class Window {

	public:

		Window(unsigned int, unsigned int);
		Window(unsigned int, unsigned int, const std::string &);

		~Window();

		GLFWwindow * getWindow() { return m_window; }

	protected:

		void init(unsigned int, unsigned int, const std::string &);
		void resize();

		unsigned int m_width;
		unsigned int m_height;

		GLFWwindow * m_window;
		Loop m_loop;

};

#endif // _WINDOW_