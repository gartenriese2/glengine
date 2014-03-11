#include "engine/engine.hpp"

#include <unistd.h>
#include <iostream>

int main() {

	Engine e;
	WindowID w1 = e.createWindow(800, 600);
	ObjectID t1 = w1.createTriangle({-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {0.f, 0.5f, 0.f});
	ObjectID t2 = w1.createTriangle({-2.f, -2.f, 1.f}, {-1.5f, -2.f, 1.f}, {-1.75f, -1.5f, 1.f}, {1.f, 1.f, 0.f});
	ObjectID t3 = w1.createCopy(t2);
	t2.attachTo(t1);
	t1.moveTo({1.5f, 0.f, 0.f});
	t2.moveTo({1.f, -0.5f, 0.f});
	
	WindowID window2 = e.createWindow(600, 800);
	ObjectID q = window2.createQuadrilateral({-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
			{{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	ObjectID copy = window2.createCopy(t1);
	ObjectID q2 = window2.createCopy(q);
	q2.moveTo({2.f, 0.f, -1.f});

	float step = 0.001f;
	float rotPerSecond = 0.33;
	long count = 0;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * step)));
		t1.rotateAround(6.28f * rotPerSecond * step, {0.f, 0.f, 1.f}, {0.f, 0.f, 0.f});
		t1.rotate(-6.28f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});
		t2.rotate(6.28f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});
		t1.scale({0.9999f, 0.9999f, 0.9999f});
		q2.rotate(6.28f * rotPerSecond * step, {0.f, 0.f, 1.f});
		if (count % 1000 == 200) t3.move(2.f, {1.f, 0.f, 0.f});
		if (count % 1000 == 800) t3.move(2.f, {-1.f, 0.f, 0.f});
		++count;
	}

	return 0;

}
