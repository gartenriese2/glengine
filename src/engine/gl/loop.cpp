#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../objects/objectinterface.hpp"
#include "../debug.hpp"

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) const {

	Basic b;
	ObjectID t1 = ObjectInterface::createTriangle({-0.5f, -0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {0.f, 0.5f, 0.f});
	ObjectID t2 = ObjectInterface::createTriangle({-2.f, -2.f, 1.f}, {-1.5f, -2.f, 1.f}, {-1.75f, -1.5f, 1.f}, {1.f, 1.f, 0.f});
	ObjectInterface::attach(t1, t2);
	ObjectInterface::moveTo(t1, {1.5f, 0.f, 0.f});
	ObjectInterface::moveTo(t2, {1.f, -0.5f, 0.f});
	// ObjectID t3 = ObjectInterface::createTriangle({0.f, 0.f, -1.f}, {2.f, 0.f, -1.f}, {1.f, 2.f, -1.f}, {{1.f, 1.f, 0.f}, {0.f, 1.f, 1.f}});
	// ObjectID q = ObjectInterface::createQuadrilateral({-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
		// {{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	b.addObjects(t1);
	b.addObjects(t2);
	Camera cam({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f}, 45.f, 800, 600, 0.1f, 10.f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{

		ObjectInterface::rotateAround(t1, 0.0005f, {0.f, 0.f, 1.f}, {0.f, 0.f, 0.f});
		ObjectInterface::rotate(t1, -0.002f, {0.f, 0.f, 1.f});
		ObjectInterface::rotate(t2, 0.002f, {0.f, 0.f, 1.f});

		/* Render here */

		b.draw(cam);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

}
