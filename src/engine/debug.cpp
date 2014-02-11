#include "debug.hpp"

Debug * Debug::s_instance = nullptr;
std::mutex Debug::s_mutex;

Debug & Debug::instance() {

	static Cleanup cleanup;
	std::lock_guard<std::mutex> guard(s_mutex);
	if (s_instance == nullptr) {
		s_instance = new Debug();
	}

	return * s_instance;

}

Debug::Cleanup::~Cleanup() {
	
	std::lock_guard<std::mutex> gaurd(Debug::s_mutex);
	delete Debug::s_instance;
	Debug::s_instance = nullptr;

}

Debug::Debug() {
}

Debug::~Debug() {
}
