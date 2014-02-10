#ifndef _ENGINE_
#define _ENGINE_

#include <string>
#include <thread>

class Engine {

	public:

		Engine();
		~Engine();

		void createWindow(unsigned int, unsigned int, const std::string & = "Default Title");

	private:

		void windowThread(unsigned int, unsigned int, const std::string &);

		std::thread * m_rendering;

};

#endif // _ENGINE_