#ifndef _DEBUG_
#define _DEBUG_

#include <mutex>
#include <iostream>

#define DEB std::cout << "DEBUG: " << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl;

class Debug {

	public:

		template<class T>
		static void log(const T & output) {
			// Please implement your favorite debug output method here!
			std::cout << output << std::endl;
		}

	protected:

		static Debug * s_instance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};

	private:

		Debug();
		virtual ~Debug();

		Debug & instance();

		static std::mutex s_mutex;

};

#endif // _DEBUG_