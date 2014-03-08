#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../debug.hpp"
#include "../passes/basicrender.hpp"

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) {

	ObjectID t1 = ObjectInterface::createTriangle({-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {0.f, 0.5f, 0.f});
	ObjectID t2 = ObjectInterface::createTriangle({-2.f, -2.f, 1.f}, {-1.5f, -2.f, 1.f}, {-1.75f, -1.5f, 1.f}, {1.f, 1.f, 0.f});
	ObjectID t22 = ObjectInterface::copyObject(t2);
	ObjectInterface::attach(t1, t2);
	ObjectInterface::moveTo(t1, {1.5f, 0.f, 0.f});
	ObjectInterface::moveTo(t2, {1.f, -0.5f, 0.f});
	ObjectID q = ObjectInterface::createQuadrilateral({-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
		{{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	ObjectID q2 = ObjectInterface::copyObject(q);
	ObjectInterface::moveTo(q2, {2.f, 0.f, -1.f});

	BasicRender r(Camera({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f}, 45.f, 1000, 800, 0.1f, 10.f));
	r.addObjects({t1, t2, q, t22, q2});
	setRendering(std::shared_ptr<Render>(&r));

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		ObjectInterface::rotateAround(t1, 0.0005f, {0.f, 0.f, 1.f}, {0.f, 0.f, 0.f});
		ObjectInterface::rotate(t1, -0.002f, {0.f, 0.f, 1.f});
		ObjectInterface::rotate(t2, 0.002f, {0.f, 0.f, 1.f});
		ObjectInterface::rotate(q2, 0.002f, {0.f, 0.f, 1.f});
		ObjectInterface::scale(t1, {0.9999f, 0.9999f, 0.9999f});

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
