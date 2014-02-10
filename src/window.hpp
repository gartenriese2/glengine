#ifndef _WINDOW_
#define _WINDOW_

#include "../includes/glew/include/GL/glew.h"
#include "../includes/glfw/include/GLFW/glfw3.h"

#include <string>

class Window {

	public:

		Window(unsigned int, unsigned int);
		Window(unsigned int, unsigned int, const std::string &);

	protected:

		void init(unsigned int, unsigned int, const std::string &);
		void resize();

		unsigned int m_width;
		unsigned int m_height;

		GLFWwindow * window;

};

#endif // _WINDOW_