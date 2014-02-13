#ifndef _ENGINE_
#define _ENGINE_

#include <string>
#include <thread>
#include <vector>

class Engine {

	public:

		Engine();
		~Engine();

		void createWindow(unsigned int, unsigned int, const std::string & = "Default Title");

	private:

		static void windowThread(unsigned int, unsigned int, const std::string &);

		std::vector<std::thread *> m_windowThreads;

};

#endif // _ENGINE_