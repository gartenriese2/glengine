#include "loop.hpp"

#include "program.hpp"
#include "../passes/basic.hpp"
#include "../objects/triangle.hpp"

Loop::Loop() {
}

void Loop::start(GLFWwindow * window) {

	Basic b;
	Triangle t2(glm::vec3(-1.f, -1.f, 0.f), glm::vec3(1.f, -1.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	b.addObjects(t2);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		b.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

}
