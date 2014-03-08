#include "engine/engine.hpp"

#include <unistd.h>
#include <iostream>

int main() {

	Engine e;
	WindowID id = e.createWindow(800, 600);
	// sleep(1);
	// e.createWindow(200, 200);
	
	// sleep(2);
	// std::cout << "Hello World!\n";
	
	return 0;

}
