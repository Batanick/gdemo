#include <GLFW/glfw3.h>
#include <memory>

#include "Renderer.h"
#include "logging.h"

static void error_callback(int error, const char *description) {
    LOG("Error: %s\n", description);
}

int main(void) {
    GLFWwindow *window;

    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "GDemo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    const std::shared_ptr<Renderer> &renderer = std::make_shared<Renderer>();
    renderer->init();

    int width = 0, height = 0;
    double lastProcessTime = glfwGetTime();
    double timeDelta = 0.0, currentTime = 0.0;

    // placing cursor to init location
    glfwSetCursorPos(window, width / 2, height / 2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        timeDelta = currentTime - lastProcessTime;
        lastProcessTime = currentTime;

        glViewport(0, 0, width, height);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        renderer->getCamera()->onBeforeRender(window, timeDelta);
        glfwGetFramebufferSize(window, &width, &height);
        glfwSetCursorPos(window, width / 2, height / 2);

        renderer->doRender(width / (float) height, (float) timeDelta);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

