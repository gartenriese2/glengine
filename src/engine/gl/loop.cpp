#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../objects/objectinterface.hpp"
#include "../debug.hpp"

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) const {

	Basic b;
	ObjectID t1 = ObjectInterface::createTriangle({-1.f, -1.f, 0.f}, {1.f, -1.f, 0.f}, {0.f, 1.f, 0.f});
	ObjectID t2 = ObjectInterface::createTriangle({-2.f, -2.f, 1.f}, {0.f, -2.f, 1.f}, {-1.f, 0.f, 1.f}, {1.f, 1.f, 0.f});
	ObjectID t3 = ObjectInterface::createTriangle({0.f, 0.f, -1.f}, {2.f, 0.f, -1.f}, {1.f, 2.f, -1.f}, {{1.f, 1.f, 0.f}, {0.f, 1.f, 1.f}});
	ObjectID q = ObjectInterface::createQuadrilateral({-2.f, -2.f, 0.f}, {2.f, -2.f, 0.f}, {2.f, 2.f, 0.f}, {-2.f, 2.f, 0.f},
		{{0.f, 1.f, 1.f}, {1.f, 0.f, 1.f}, {1.f, 1.f, 1.f}, {0.f, 0.f, 1.f}});
	b.addObjects(t1);
	b.addObjects(t2);
	b.addObjects(t3);
	b.addObjects(q);
	Camera cam({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f}, 45.f, 800, 600, 0.1f, 10.f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		ObjectInterface::rotate(t1, 0.001f, {0.f, 0.f, 1.f});
		ObjectInterface::rotate(t3, 0.0005f, {0.f, 0.f, 1.f});
		ObjectInterface::rotate(t2, 0.0001f, {1.f, 0.f, 0.f});

		/* Render here */

		b.draw(cam);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

}
