#include "windowthread.hpp"

WindowThread::WindowThread(std::shared_ptr<Window> ptr, unsigned int width, unsigned int height, const std::string & title)
  : std::thread(&WindowThread::windowFunction, ptr, width, height, title)
{
}

WindowThread::~WindowThread() {
	join();
}

void WindowThread::windowFunction(std::shared_ptr<Window> ptr, unsigned int width, unsigned int height, const std::string & title) {

	ptr = std::shared_ptr<Window>(new Window(width, height, title));

}
