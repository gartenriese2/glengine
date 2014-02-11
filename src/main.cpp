#include "engine.hpp"

#include <unistd.h>

int main() {

	Engine e;
	e.createWindow(800, 600);
	sleep(1);
	e.createWindow(200, 200);
	
	sleep(5);
	
	return 0;

}
