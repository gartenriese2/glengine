#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../objects/triangle.hpp"

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) const {

	Basic b;
	Triangle t1({-1.f, -1.f, 0.f}, {1.f, -1.f, 0.f}, {0.f, 1.f, 0.f});
	Triangle t2({-2.f, -2.f, 1.f}, {0.f, -2.f, 1.f}, {-1.f, 0.f, 1.f}, {1.f, 1.f, 0.f});
	Triangle t3({0.f, 0.f, -1.f}, {2.f, 0.f, -1.f}, {1.f, 2.f, -1.f}, {{1.f, 1.f, 0.f}, {0.f, 1.f, 1.f}});
	b.addObjects(t1);
	b.addObjects(t2);
	b.addObjects(t3);
	Camera cam({0.f, 0.f, 5.f}, {0.f, 0.f, -1.f}, {0.f, 1.f, 0.f}, 45.f, 800, 600, 0.1f, 10.f);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		t1.rotate(0.001f, {0.f, 0.f, 1.f});
		t3.rotate(0.0005f, {0.f, 0.f, 1.f});
		t2.rotate(0.0001f, {1.f, 0.f, 0.f});

		/* Render here */

		b.draw(cam);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

}
