#ifndef _ENGINE_
#define _ENGINE_

#include <string>
#include <thread>
#include <map>
#include <memory>

using WindowID = unsigned int;

class Engine {

	public:

		Engine();
		~Engine();

		WindowID createWindow(unsigned int, unsigned int, const std::string & = "Default Title");

	private:

		static void windowThread(unsigned int, unsigned int, const std::string &);

		void init();

		std::map<WindowID, std::unique_ptr<std::thread>> m_windowThreads;

};

#endif // _ENGINE_