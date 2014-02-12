#ifndef _WINDOW_
#define _WINDOW_

#include "gl/loop.hpp"
#include "gl/glincludes.hpp"

#include <string>
#include <thread>

class Window {

	public:

		Window(unsigned int, unsigned int);
		Window(unsigned int, unsigned int, const std::string &);

		~Window();

	protected:

		void init(unsigned int, unsigned int, const std::string &);
		void resize();

		unsigned int m_width;
		unsigned int m_height;

		GLFWwindow * m_window;
		Loop m_loop;

};

#endif // _WINDOW_