#ifndef _WINDOWTHREAD_
#define _WINDOWTHREAD_

#include <thread>
#include <string>

class WindowThread : public std::thread {

	public:

		WindowThread(unsigned int, unsigned int, const std::string & = "Default Title");
		WindowThread(const WindowThread &) = delete;
		WindowThread(WindowThread &&) = delete;
		WindowThread & operator=(const WindowThread &) = delete;
		WindowThread & operator=(WindowThread &&) = delete;
		~WindowThread();

	private:

		static void windowFunction(unsigned int, unsigned int, const std::string &);

};

#endif // _WINDOWTHREAD_