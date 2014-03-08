#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../debug.hpp"
#include "../passes/basicrender.hpp"

#include <mutex>

static std::mutex s_mutex;

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) {

	ObjectID t1 = 1;
	addCommand([t1](){
		ObjectInterface::createTriangle(t1, {-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {0.f, 0.5f, 0.f});
	});
	ObjectID t2 = 2;
	addCommand([t2](){
		ObjectInterface::createTriangle(t2, {-2.f, -2.f, 1.f}, {-1.5f, -2.f, 1.f}, {-1.75f, -1.5f, 1.f}, {1.f, 1.f, 0.f});
	});
	ObjectID t22 = 3;
	addCommand([t2, t22](){
		ObjectInterface::copyObject(t2, t22);
	});
	addCommand([t1, t2](){
		ObjectInterface::attach(t1, t2);
	});
	addCommand([t1](){
		ObjectInterface::moveTo(t1, {1.5f, 0.f, 0.f});
	});
	addCommand([t2](){
		ObjectInterface::moveTo(t2, {1.f, -0.5f, 0.f});
	});
	ObjectID q = 4;
	addCommand([q](){
		ObjectInterface::createQuadrilateral(q, {-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
			{{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	});
	ObjectID q2 = 5;
	addCommand([q, q2](){
		ObjectInterface::copyObject(q, q2);
	});
	addCommand([q2](){
		ObjectInterface::moveTo(q2, {2.f, 0.f, -1.f});
	});

	BasicRender r(Camera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f}, 45.f, 1000, 800, 0.1f, 10.f));
	r.addObjects({t1, t2, q, t22, q2});
	setRendering(std::shared_ptr<Render>(&r));

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		addCommand([t1](){
			ObjectInterface::rotateAround(t1, 0.0005f, {0.f, 0.f, 1.f}, {0.f, 0.f, 0.f});
		});
		addCommand([t1](){
			ObjectInterface::rotate(t1, -0.002f, {0.f, 0.f, 1.f});
		});
		addCommand([t2](){
			ObjectInterface::rotate(t2, 0.002f, {0.f, 0.f, 1.f});
		});
		addCommand([q2](){
			ObjectInterface::rotate(q2, 0.002f, {0.f, 0.f, 1.f});
		});
		addCommand([t1](){
			ObjectInterface::scale(t1, {0.9999f, 0.9999f, 0.9999f});
		});

		emptyCommands();

		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

}

void Loop::render() {

	if (m_rendering) {
		m_rendering->draw();
	}

}

void Loop::addCommand(std::function<void()> func) {

	std::lock_guard<std::mutex> lock(s_mutex);

	m_commands.push(func);

}

void Loop::emptyCommands() {

	std::lock_guard<std::mutex> lock(s_mutex);

	while (!m_commands.empty()) {
		m_commands.front()();
		m_commands.pop();
	}

}
