#include "engine/engine.hpp"

#include <unistd.h>
#include <iostream>

int main() {

	Engine e;
	WindowID id = e.createWindow(800, 600);
	sleep(1);
	e.createTriangle(id, {-1.f, 0.f, 2.f}, {1.f, 0.f, 2.f}, {0.f, 1.f, 2.f}, {0.f, 1.f, 0.f});
	sleep(1);
	WindowID id2 = e.createWindow(600, 800);
	sleep(1);
	e.createQuadrilateral(id2, {-1.f, -1.f, 0.f}, {1.f, -1.f, 0.f}, {1.f, 1.f, 0.f}, {-1.f, 1.f, 0.f},
		{{1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}});
	
	return 0;

}
