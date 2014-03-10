#ifndef _DEBUG_
#define _DEBUG_

#include <mutex>
#include <iostream>
#include <string>
#include "glmincludes.hpp"

#define DEB Debug::log("DEBUG: " + std::string(__FILE__) + " " + __FUNCTION__ + " " + std::to_string(__LINE__));

class Debug {

	public:

		template<class T>
		static void log(const T & output) {
			std::lock_guard<std::mutex> guard(s_mutex);
			// Please implement your favorite debug output method here!
			std::cout << output << std::endl;
		}

		static void log(const glm::vec3 & vec) {
			log("vec3: " + std::to_string(vec.x) + "|" + std::to_string(vec.y) + "|" + std::to_string(vec.z));
		}

		static void logGL();

	protected:

		static Debug * s_instance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};

	private:

		Debug();
		Debug(const Debug &) = delete;
		Debug(Debug &&) = delete;
		Debug & operator=(const Debug &) = delete;
		Debug & operator=(Debug &&) = delete;
		virtual ~Debug();

		Debug & instance();

		static std::mutex s_mutex;

};

#endif // _DEBUG_