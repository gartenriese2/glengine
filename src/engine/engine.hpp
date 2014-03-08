#ifndef _ENGINE_
#define _ENGINE_

#include "windowthread.hpp"
#include "objects/objectinterface.hpp"

#include <string>
#include <thread>
#include <map>
#include <memory>

using WindowID = unsigned int;

class Engine {

	public:

		Engine();
		Engine(const Engine &) = delete;
		Engine(Engine &&) = delete;
		Engine & operator=(const Engine &) = delete;
		Engine & operator=(Engine &&) = delete;
		~Engine();

		WindowID createWindow(unsigned int, unsigned int, const std::string & = "Default Title");

		ObjectID createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);

	private:

		void init();

		std::map<WindowID, std::unique_ptr<WindowThread>> m_windowThreads;

};

#endif // _ENGINE_