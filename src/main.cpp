#include "engine/engine.hpp"
#include "engine/debug.hpp"

#include <unistd.h>
#include <iostream>

Engine e;

void addControls(WindowID & w, CameraID & cam) {

	w.addKeyEvent(GLFW_KEY_ESCAPE, [&](){
		w.close();
		glfwTerminate();
	});
	w.addKeyEvent(GLFW_KEY_R, [&](){
		cam.reset();
	});
	w.addKeyEvent(GLFW_KEY_SPACE, [&](){
		cam.rotate(0.05f, cam.getDir());
	});
	w.addKeyEvent(GLFW_KEY_W, [&](){
		cam.move(glm::normalize(cam.getDir()) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 0.2f : 0.05f));
	});
	w.addKeyEvent(GLFW_KEY_S, [&](){
		cam.move(-glm::normalize(cam.getDir()) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 0.2f : 0.05f));
	});
	w.addKeyEvent(GLFW_KEY_Q, [&](){
		cam.move(glm::normalize(cam.getUp()) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 0.2f : 0.05f));
	});
	w.addKeyEvent(GLFW_KEY_E, [&](){
		cam.move(-glm::normalize(cam.getUp()) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 0.2f : 0.05f));
	});
	w.addKeyEvent(GLFW_KEY_A, [&](){
		cam.move(glm::normalize(glm::cross(cam.getUp(), cam.getDir())) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 0.2f : 0.05f));
	});
	w.addKeyEvent(GLFW_KEY_D, [&](){
		cam.move(-glm::normalize(glm::cross(cam.getUp(), cam.getDir())) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 0.2f : 0.05f));
	});

	w.setScrollEvent([&](double xoffset, double yoffset){
		cam.moveTo(cam.getPos() + static_cast<float>(yoffset) * glm::normalize(cam.getDir()));
	});

}

void ampelDemo() {

	// WindowID w = e.createFullscreenWindow(2560, 1440);
	WindowID w = e.createWindow(1024, 768);

	CameraID cam = w.createCamera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic = w.createBasicRendering(cam);
	basic.set();
	
	addControls(w, cam);
	double oldX = -1.0, oldY = -1.0;
	w.setMouseMoveEvent([&](double xpos, double ypos){
		
		if (oldX != -1.0 && oldY != -1.0 && w.isLeftMouseButtonPressed()) {
			cam.yaw(-(oldX - xpos) * 0.001f);
			cam.pitch((oldY - ypos) * 0.001f);
		}
		oldX = xpos;
		oldY = ypos;

	});

	ObjectID red = w.createCircle({0.f, 1.5f, 0.f}, {0.f, 0.f, 1.f}, 0.5f, 50, {0.25f, 0.f, 0.f});
	ObjectID orange = w.createCircle({0.f, 0.f, 0.f}, {0.f, 0.f, 1.f}, 0.5f, 50, {1.0f, 0.5f, 0.f});
	ObjectID green = w.createCircle({0.f, -1.5f, 0.f}, {0.f, 0.f, 1.f}, 0.5f, 50, {0.f, 0.25f, 0.f});
	basic.addObjects({red, orange, green});

	float step = 0.001f;
	long count = 0;
	while (1) {

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * step)));

		if (count % 3000 == 1000) {
			orange.scaleColor(4.f);
		}
		if (count % 3000 == 1500) {
			orange.scaleColor(0.25f);
			red.scaleColor(0.25f);
			green.scaleColor(4.f);
		}
		if (count % 3000 == 2500) {
			orange.scaleColor(4.f);
			green.scaleColor(0.25f);
		}
		if (count % 3000 == 0) {
			orange.scaleColor(0.25f);
			red.scaleColor(4.f);
		}

		++count;

	}

}

void rotateDemo() {

	WindowID w = e.createWindow(800, 800);

	CameraID cam = w.createCamera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic = w.createBasicRendering(cam);
	basic.set();

	ObjectID t1 = w.createTriangle({-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {0.f, 0.5f, 0.f});
	ObjectID t2 = w.createTriangle({-2.f, -2.f, 1.f}, {-1.5f, -2.f, 1.f}, {-1.75f, -1.5f, 1.f}, {1.f, 1.f, 0.f});
	ObjectID t3 = w.createCopy(t2);
	basic.addObjects({t1, t2, t3});

	t2.attachTo(t1);
	t1.moveTo({1.5f, 0.f, 0.f});
	t2.moveTo({1.f, -0.5f, 0.f});

	float step = 0.01335f;
	float rotPerSecond = 0.33f;
	long count = 0;
	while (1) {
		
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * step)));
		
		t1.rotateAround(6.28f * rotPerSecond * step, {0.f, 0.f, 1.f}, {0.f, 0.f, 0.f});
		t1.rotate(-6.28f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});
		t2.rotate(6.28f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});
		t1.scale({0.9999f, 0.9999f, 0.9999f});
		if (count % 1000 == 200) t3.move(2.f, {1.f, 0.f, 0.f});
		if (count % 1000 == 800) t3.move(2.f, {-1.f, 0.f, 0.f});

		++count;

	}

}

void secondWindowDemo() {

	WindowID w1 = e.createWindow(800, 600);
	WindowID w2 = e.createWindow(600, 800);

	CameraID cam1 = w1.createCamera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic1 = w1.createBasicRendering(cam1);
	basic1.set();
	CameraID cam2 = w2.createCamera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic2 = w2.createBasicRendering(cam2);
	basic2.set();

	ObjectID q = w2.createQuadrilateral({-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
			{{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	ObjectID q2 = w2.createCopy(q);

	basic2.addObjects({q, q2});

	q2.moveTo({2.f, 0.f, -1.f});

	float step = 0.001f;
	float rotPerSecond = 0.33;
	while (1) {

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * step)));

		q2.rotate(-6.28f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});

	}

}

void test() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 2.5f, 5.f}, {0.f, -0.5f, -1.f}, {0.f, 1.f, -0.5f});
	RenderID basic = w.createBasicRendering(cam);
	RenderID normal = w.createNormalRendering(cam);
	basic.set();

	addControls(w, cam);
	double oldX = -1.0, oldY = -1.0;
	w.setMouseMoveEvent([&](double xpos, double ypos){
		
		if (oldX != -1.0 && oldY != -1.0 && w.isLeftMouseButtonPressed()) {
			cam.yaw(-(oldX - xpos) * 0.001f);
			cam.pitch((oldY - ypos) * 0.001f);
		}
		oldX = xpos;
		oldY = ypos;

	});
	bool n_toggled = false;
	w.addKeyEvent(GLFW_KEY_N, [&](){
		if (n_toggled) {
			n_toggled = false;
			basic.set();
		} else {
			n_toggled = true;
			normal.set();
		}
	});

	// ObjectID cube = w.createCuboid({-1.f, -1.f, 1.f}, {1.f, -1.f, 1.f}, {-1.f, -1.f, -1.f}, {-1.f, 1.f, 1.f});
	// cube.scale({1.f, 0.5f, 1.f});
	// basic.addObjects({cube});
	// normal.addObjects({cube});

	ObjectID sphere = w.createSphere({0.f, 0.f, 0.f}, 1.f, 40, 50);
	sphere.scale({2.f, 0.5f, 1.f});
	basic.addObjects({sphere});
	normal.addObjects({sphere});

	float step = 0.001f;
	float rotPerSecond = 0.33f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
		sphere.rotate(6.28f * rotPerSecond * step, {0.f, 1.f, 0.f});
	}

}

int main() {

	// ampelDemo();
	// rotateDemo();
	// secondWindowDemo();
	test();

	return 0;

}
