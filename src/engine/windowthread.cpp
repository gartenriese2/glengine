#include "windowthread.hpp"

#include "window.hpp"

WindowThread::WindowThread(unsigned int width, unsigned int height, const std::string & title)
  : std::thread(&WindowThread::windowFunction, width, height, title)
{
}

WindowThread::~WindowThread() {
	join();
}

void WindowThread::windowFunction(unsigned int width, unsigned int height, const std::string & title) {

	Window w(width, height, title);

}
