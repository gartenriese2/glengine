#include "engine.hpp"
#include "window.hpp"

#include <unistd.h>
#include <thread>

void threadTest() {

	Window w(800, 600, "Hallo Welt");

}

int main() {

	// Window w(800, 600, "Hallo Welt");
	// Engine e;
	// e.createWindow(800, 600);
	std::thread t(threadTest);
	sleep(5);
	t.join();
	return 0;

}
