#ifndef _WINDOW_
#define _WINDOW_

#include "gl/loop.hpp"
#include "gl/glincludes.hpp"

#include <string>
#include <thread>

class Window {

	public:
		
		Window(unsigned int, unsigned int, const std::string &);
		Window(const Window &) = delete;
		Window(Window &&) = delete;
		Window & operator=(const Window &) = delete;
		Window & operator=(Window &&) = delete;
		~Window();

		void start();

		Loop & getLoop() { return m_loop; }

	protected:

		void resize();

		unsigned int m_width;
		unsigned int m_height;
		std::string m_title;

		GLFWwindow * m_window;
		Loop m_loop;

	private:

		static void debugCallback(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, GLvoid *);
		static void formatDebugOutput(char outStr[], size_t, GLenum, GLenum, GLuint, GLenum, const char *);

};

#endif // _WINDOW_