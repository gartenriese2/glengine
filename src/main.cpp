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
	float oldX = -1.0, oldY = -1.0;
	w.setMouseMoveEvent([&](float xpos, float ypos){

		if (oldX != -1.0 && oldY != -1.0 && w.isLeftMouseButtonPressed()) {
			cam.yaw(-(oldX - xpos) * 0.001f);
			cam.pitch((oldY - ypos) * 0.001f);
		}
		oldX = xpos;
		oldY = ypos;

	});

	ObjectID red {w.createCircleInstance()};
	red.moveTo({0.f, 1.5f, 0.f});
	red.setColor({0.25f, 0.f, 0.f});
	ObjectID orange {w.createCircleInstance()};
	orange.setColor({1.0f, 0.5f, 0.f});
	ObjectID green {w.createCircleInstance()};
	green.moveTo({0.f, -1.5f, 0.f});
	green.setColor({0.f, 0.25f, 0.f});
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

	CameraID cam = w.createCamera({0.f, 0.f, 10.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
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

	CameraID cam1 = w1.createCamera({0.f, 0.f, 10.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic1 = w1.createBasicRendering(cam1);
	basic1.set();
	CameraID cam2 = w2.createCamera({0.f, 0.f, 10.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic2 = w2.createBasicRendering(cam2);
	basic2.set();

	ObjectID q = w2.createQuadrilateral({-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
			{{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	ObjectID q2 = w2.createCopy(q);
	ObjectID q3 {w1.createQuadrilateralInstance()};

	basic2.addObjects({q, q2});
	basic1.addObjects({q3});

	q2.moveTo({2.f, 0.f, -1.f});

	float step = 0.001f;
	float rotPerSecond = 0.33f;
	while (1) {

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * step)));

		q2.rotate(-6.28f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});
		q3.rotate(3.14f * 2*rotPerSecond * step, {0.f, 0.f, 1.f});

	}

}

void test() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 2.5f, 5.f}, {0.f, -0.5f, -1.f}, {0.f, 1.f, -0.5f});
	LightID light = w.createLight({10.f, 0.f, 0.f}, {-1.f, 0.f, -0.1f});
	LightID spotlight = w.createLight({0.f, 0.f, -5.f}, {0.f, 0.f, -1.f});
	ObjectID flashlight = w.createCone({0.f, 0.f, -3.5f}, {0.f, 0.f, -1.f}, 1.5f, 0.3f, 0.3f, 50, {0.2f, 0.2f, 0.4f});
	spotlight.setAsSpotLight();
	spotlight.setSpotCutoff(0.1f);
	RenderID basic = w.createBasicRendering(cam);
	RenderID normal = w.createNormalRendering(cam);
	RenderID lighting = w.createBasicLightingRendering(cam, {spotlight, light});
	lighting.set();

	addControls(w, cam);
	float oldX = -1.0f, oldY = -1.0f;
	w.setMouseMoveEvent([&](float xpos, float ypos){

		if (oldX != -1.0f && oldY != -1.0f && w.isLeftMouseButtonPressed()) {
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
			lighting.set();
		} else {
			n_toggled = true;
			normal.set();
		}
	});

	w.addKeyEvent(GLFW_KEY_I, [&](){
		spotlight.move(glm::normalize(spotlight.getDirection()) * 0.1f);
		flashlight.move(0.1f, glm::normalize(spotlight.getDirection()));
	});
	w.addKeyEvent(GLFW_KEY_K, [&](){
		spotlight.move(-glm::normalize(spotlight.getDirection()) * 0.1f);
		flashlight.move(0.1f, -glm::normalize(spotlight.getDirection()));
	});

	ObjectID sphere = w.createSphere({0.f, 0.f, 0.f}, 1.f, 40, 50);
	ObjectID wall = w.createQuadrilateral({-10.f, -10.f, -10.f}, {10.f, -10.f, -10.f}, {10.f, 10.f, -10.f},
		{-10.f, 10.f, -10.f}, {0.5f, 0.5f, 0.5f});
	sphere.scale({2.f, 0.5f, 1.f});
	basic.addObjects({sphere, wall, flashlight});
	normal.addObjects({sphere, wall, flashlight});
	lighting.addObjects({sphere, wall, flashlight});

	// gold
	sphere.setAmbient({0.24725f, 0.1995f, 0.0745f});
	sphere.setDiffuse({0.75164f, 0.60648f, 0.22648f});
	sphere.setSpecular({0.628281f, 0.555802f, 0.366065f});
	sphere.setShininess(51.2f);
	sphere.setColor({1.f, 0.843f, 0.f});

	// white plastic
	wall.setAmbient({0.f, 0.f, 0.f});
	wall.setDiffuse({0.55f, 0.55f, 0.55f});
	wall.setSpecular({0.70f, 0.70f, 0.70f});
	wall.setShininess(32.f);

	// chrome
	flashlight.setAmbient({0.25f, 0.25f, 0.25f});
	flashlight.setDiffuse({0.4f, 0.4f, 0.4f});
	flashlight.setSpecular({0.774597f, 0.774597f, 0.774597f});
	flashlight.setShininess(0.6f * 128.f);

	// w.addKeyEvent(GLFW_KEY_P, [&](){
	// 	sphere.setAmbient(sphere.getAmbient() * 1.1f);
	// });
	// w.addKeyEvent(GLFW_KEY_O, [&](){
	// 	sphere.setAmbient(sphere.getAmbient() * 0.9f);
	// });

	float step = 0.001f;
	float rotPerSecond = 0.33f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
		sphere.rotate(6.28f * rotPerSecond * step, {0.f, 1.f, 0.f});
	}

}

void coneTest() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});
	RenderID basic = w.createBasicRendering(cam);
	RenderID normal = w.createNormalRendering(cam);

	basic.set();

	addControls(w, cam);
	float oldX = -1.0, oldY = -1.0;
	w.setMouseMoveEvent([&](float xpos, float ypos){

		if (oldX != -1.0f && oldY != -1.0f && w.isLeftMouseButtonPressed()) {
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

	ObjectID cone = w.createCone({0.f, 0.f, 0.f}, {1.f, -1.f, 1.f}, 2.f, 1.f, 1.f, 50);
	cone.move(1.f, {1.f, 1.f, 0.f});
	basic.addObjects({cone});
	normal.addObjects({cone});

	float step = 0.001f;
	float rotPerSecond = 0.33f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
		cone.rotate(6.28f * rotPerSecond * step, {1.f, 1.f, 0.f});
	}

}

void fbo() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 2.5f, 5.f}, {0.f, -0.5f, -1.f}, {0.f, 1.f, -0.5f});
	RenderID gbuffer = w.createGBufferRendering(cam);
	gbuffer.set();

	ObjectID sphere = w.createSphere({0.f, 0.f, 0.f}, 1.f, 40, 50);
	sphere.scale({2.f, 0.5f, 1.f});
	ObjectID wall = w.createQuadrilateral({-10.f, -10.f, -10.f}, {10.f, -10.f, -10.f}, {10.f, 10.f, -10.f},
		{-10.f, 10.f, -10.f}, {0.5f, 0.5f, 0.5f});

	gbuffer.addObjects({sphere, wall});

	// gold
	sphere.setAmbient({0.24725f, 0.1995f, 0.0745f});
	sphere.setDiffuse({0.75164f, 0.60648f, 0.22648f});
	sphere.setSpecular({0.628281f, 0.555802f, 0.366065f});
	sphere.setShininess(51.2f);
	sphere.setColor({1.f, 0.843f, 0.f});

	addControls(w, cam);
	float oldX = -1.0f, oldY = -1.0f;
	w.setMouseMoveEvent([&](float xpos, float ypos){

		if (oldX != -1.0f && oldY != -1.0f && w.isLeftMouseButtonPressed()) {
			cam.yaw(-(oldX - xpos) * 0.001f);
			cam.pitch((oldY - ypos) * 0.001f);
		}
		oldX = xpos;
		oldY = ypos;

	});

	float step = 0.001f;
	float rotPerSecond = 0.33f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
		sphere.rotate(6.28f * rotPerSecond * step, {0.f, 1.f, 0.f});
	}

}

void spline() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 2.5f, 5.f}, {0.f, -0.5f, -1.f}, {0.f, 1.f, -0.5f});
	RenderID basic = w.createBasicRendering(cam);
	basic.set();

	ObjectID spline = w.createSpline({0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {2.f, 2.f, 0.f}, {0.f, 1.f, 0.f},
		{0.f, 0.f, 1.f}, 0.5f, 0.5f, 100, 100.f, {0.f, 1.f, 0.f});
	ObjectID spline2 = w.createSpline({0.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, {0.f, -2.f, 0.f}, {1.f, 0.f, 0.f},
		{0.f, 0.f, 1.f}, 0.5f, 0.5f, 100, 100.f, {0.f, 1.f, 0.f});
	ObjectID spline3 = w.createSpline({0.f, -2.f, 0.f}, {2.f, 0.f, 0.f}, {4.f, -6.f, 0.f}, {0.f, -2.f, 0.f},
		{0.f, 0.f, 1.f}, 0.5f, 0.5f, 10, 100.f, {0.f, 1.f, 0.f});
	basic.addObjects({spline, spline2, spline3});

	addControls(w, cam);

	float step = 0.001f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
	}

}

void raytracing() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 0.f, 10.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f});

	addControls(w, cam);
	float oldX = -1.0f, oldY = -1.0f;
	w.setMouseMoveEvent([&](float xpos, float ypos){

		if (oldX != -1.0f && oldY != -1.0f && w.isLeftMouseButtonPressed()) {
			cam.yaw(-(oldX - xpos) * 0.001f);
			cam.pitch((oldY - ypos) * 0.001f);
		}
		oldX = xpos;
		oldY = ypos;

	});

	LightID spotlight = w.createLight({0.f, 4.9f, 0.f}, {0.f, -1.f, 0.f});
	spotlight.setAsSpotLight();
	spotlight.setSpotCutoff(0.1f);
	spotlight.setSpotExponent(2.f);

	LightID spotlight2 = w.createLight({4.9f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, {1.f, 0.f, 0.f});
	spotlight2.setAsSpotLight();
	spotlight2.setSpotCutoff(0.1f);
	spotlight2.setSpotExponent(2.f);
	//spotlight.setColor({0.f, 0.f, 1.f});
	RenderID lighting = w.createRaytracingRendering(cam, {spotlight, spotlight2});
	// RenderID lighting = w.createBasicLightingRendering(cam, {spotlight});
	lighting.set();

	ObjectID wallBack = w.createQuadrilateral({-5.f, -5.f, -5.f}, {5.f, -5.f, -5.f}, {5.f, 5.f, -5.f},
		{-5.f, 5.f, -5.f}, {1.f, 1.f, 1.f});
	ObjectID wallLeft = w.createQuadrilateral({-5.f, -5.f, 5.f}, {-5.f, -5.f, -5.f}, {-5.f, 5.f, -5.f},
		{-5.f, 5.f, 5.f}, {0.f, 1.f, 0.f});
	ObjectID wallRight = w.createQuadrilateral({5.f, -5.f, -5.f}, {5.f, -5.f, 5.f}, {5.f, 5.f, 5.f},
		{5.f, 5.f, -5.f}, {1.f, 0.f, 0.f});
	ObjectID floor = w.createQuadrilateral({-5.f, -5.f, 5.f}, {5.f, -5.f, 5.f}, {5.f, -5.f, -5.f},
		{-5.f, -5.f, -5.f}, {1.f, 1.f, 1.f});
	ObjectID ceiling = w.createQuadrilateral({-5.f, 5.f, -5.f}, {5.f, 5.f, -5.f}, {5.f, 5.f, 5.f},
		{-5.f, 5.f, 5.f}, {1.f, 1.f, 1.f});

	ObjectID lightbulb = w.createSphere({0.f, 4.9f, 0.f}, 0.2f, 5, 5, {1.f, 1.f, 1.f});

	ObjectID cube = w.createCuboid({-4.f, -5.f, -1.f}, {-1.f, -5.f, -1.f}, {-4.f, -5.f, -4.f},
		{-4.f, -2.f, -1.f}, {0.f, 0.f, 0.9f});
	cube.rotate(0.785f, {0.f, 1.f, 0.f});
	ObjectID cube2 = w.createCuboid({-1.f, -1.f, 1.f}, {1.f, -1.f, 1.f}, {-1.f, 1.f, 1.f},
		{-1.f, -1.f, -1.f}, {0.9f, 0.9f, 0.f});
	ObjectID cube3 = w.createCuboidInstance();
	cube3.move(1.f, {2.f, 2.f, 0.f});
	cube3.setColor({0.8f, 0.f, 0.8f});
	cube3.setShininess(250.f);
	// ObjectID sphere = w.createSphere({2.5f, -3.f, -2.5f}, 2.f, 12, 12, {0.9f, 0.9f, 0.9f});

	lighting.addObjects({wallBack, wallLeft, wallRight, floor, ceiling, cube, cube2, cube3});

	float step = 0.001f;
	float rotPerSecond = 0.33f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
		cube2.rotate(6.28f * rotPerSecond * step, {0.f, 1.f, 0.f});
		cube3.rotate(3.14f * rotPerSecond * step, {1.f, 0.f, 0.f});
	}

}

#include "mapcity/road.hpp"
#include "mapcity/path.hpp"
#include "mapcity/grid.hpp"

void mapcity() {

	WindowID w = e.createWindow(1280, 720);
	CameraID cam = w.createCamera({0.f, 200.f, 0.f}, {0.f, -1.f, 0.f}, {0.f, 0.f, -1.f});

	w.addKeyEvent(GLFW_KEY_W, [&](){
		cam.move(glm::vec3(0.f, 0.f, -1.f) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 2.f : 0.5f));
	});
	w.addKeyEvent(GLFW_KEY_S, [&](){
		cam.move(glm::vec3(0.f, 0.f, 1.f) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 2.f : 0.5f));
	});
	w.addKeyEvent(GLFW_KEY_A, [&](){
		cam.move(glm::vec3(-1.f, 0.f, 0.f) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 2.f : 0.5f));
	});
	w.addKeyEvent(GLFW_KEY_D, [&](){
		cam.move(glm::vec3(1.f, 0.f, 0.f) * (w.isKeyPressed(GLFW_KEY_LEFT_SHIFT) ? 2.f : 0.5f));
	});

	RenderID basic = w.createBasicRendering(cam);
	basic.set();

	ObjectID ground = w.createQuadrilateral({-200.f, 0.f, 200.f}, {200.f, 0.f, 200.f}, {200.f, 0.f, -200.f},
		{-200.f, 0.f, -200.f}, {0.f, 0.7f, 0.f});
	basic.addObjects({ground});

	// Road r1({{0.f, 50.f}, {0.f, -50.f}, {10.f, -60.f}, {60.f, -60.f}, {80.f, -80.f}}, w, basic);

	Path p0(Path::createPathFromControlPoints({{-10.f, 0.1f, 0.f}, {0.f, 0.1f, 0.f}, {30.f, 0.1f, 0.f}, {50.f, 0.1f, 20.f},
		{50.f, 0.1f, 50.f}, {50.f, 0.1f, 60.f}}));

	Path p3(Path::createPathFromControlPoints({1.f, 0.1f, 30.f}, {10.f, 0.1f, 20.f}, {40.f, 0.1f, -10.f},
		{50.f, 0.1f, -20.f}));

	ObjectID testpath0 = w.createSpline(p0.getPoints(), {0.f, 1.f, 0.f}, 0.1f, {0.8f, 0.8f, 0.f});
	ObjectID testpath3 = w.createSpline(p3.getPoints(), {0.f, 1.f, 0.f}, 0.1f, {0.8f, 0.8f, 0.f});
	basic.addObjects({testpath0, testpath3});

	float step = 0.001f;
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 *  step)));
	}

}

int main() {

	//ampelDemo();
	//rotateDemo();
	//secondWindowDemo();
	//test();
	//coneTest();
	//fbo();
	//spline();
	raytracing();
	//mapcity();

	return 0;

}
