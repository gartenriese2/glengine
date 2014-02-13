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
	Camera cam(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f), 45.f, 800, 600, 0.1f, 10.f);

	while (!glfwWindowShouldClose(window))
	{
		t2.rotate(0.001f, {0.f, 0.f, 1.f});

		/* Render here */

		b.draw(cam);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

}
