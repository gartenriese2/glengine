#include "loop.hpp"

Loop::Loop() {

}

void Loop::start(GLFWwindow * window) {

	while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

}
