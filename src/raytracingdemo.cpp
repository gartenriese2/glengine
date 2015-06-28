#include "raytracingdemo.hpp"

#include "engine/passes/raytracingrender.hpp"
#include "engine/objects/objectinterface.hpp"
class Quadrilateral;

RaytracingDemo::RaytracingDemo()
  : m_engine{},
  	m_window{m_engine.createWindow(1280, 720)},
  	m_cam{m_window.createCamera({0.f, 0.f, 10.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f})}
  	//m_render{m_window.createRaytracingRendering(m_cam, {})}
{
	initControls();
	initObjects();
	initLights();

}

RaytracingDemo::~RaytracingDemo() {

}

void RaytracingDemo::run() {

	LightID spotlight = m_window.createLight({0.f, 4.9f, 0.f}, {0.f, -1.f, 0.f});
	spotlight.setAsSpotLight();
	spotlight.setSpotCutoff(0.1f);
	spotlight.setSpotExponent(2.f);
	//spotlight.setColor({0.f, 0.f, 1.f});
	RenderID lighting = m_window.createRaytracingRendering(m_cam, {spotlight});
	lighting.set();

	while (1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}

void RaytracingDemo::initControls() {

	m_window.addKeyEvent(GLFW_KEY_ESCAPE, [&](){
		m_window.close();
		glfwTerminate();
	});

}

void RaytracingDemo::initObjects() {

	m_objects.emplace_back(m_window.createQuadrilateral({-5.f, -5.f, -5.f}, {5.f, -5.f, -5.f},
														{5.f, 5.f, -5.f}, {-5.f, 5.f, -5.f},
														{1.f, 1.f, 1.f}));
	m_objects.emplace_back(m_window.createQuadrilateral({-5.f, -5.f, 5.f}, {-5.f, -5.f, -5.f},
														{-5.f, 5.f, -5.f}, {-5.f, 5.f, 5.f},
														{0.f, 1.f, 0.f}));
	m_objects.emplace_back(m_window.createQuadrilateral({5.f, -5.f, -5.f}, {5.f, -5.f, 5.f},
														{5.f, 5.f, 5.f}, {5.f, 5.f, -5.f},
														{1.f, 0.f, 0.f}));
	m_objects.emplace_back(m_window.createQuadrilateral({-5.f, -5.f, 5.f}, {5.f, -5.f, 5.f},
														{5.f, -5.f, -5.f}, {-5.f, -5.f, -5.f},
														{1.f, 1.f, 1.f}));
	m_objects.emplace_back(m_window.createQuadrilateral({-5.f, 5.f, -5.f}, {5.f, 5.f, -5.f},
														{5.f, 5.f, 5.f}, {-5.f, 5.f, 5.f},
														{1.f, 1.f, 1.f}));

}

void RaytracingDemo::initLights() {

	m_lights.emplace_back(m_window.createLight({0.f, 4.9f, 0.f}, {0.f, -1.f, 0.f}));

}
