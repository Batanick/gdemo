//
// Created by Evgenii Loikov
//

#include "FpsCounter.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static double const SECOND = 1;

double FpsCounter::onFrame() {
    const double currentTime = glfwGetTime();
    fpsCounter++;

    const double timeDelta = currentTime - lastTickTime;
    timeCounter += timeDelta;
    if (timeCounter > SECOND) {
        currentFps = (fpsCounter) / timeCounter;

        fpsCounter = 0;
        timeCounter = 0;
    }

    lastTickTime = currentTime;
    return timeDelta;
}

double FpsCounter::getFps() const {
    return currentFps;
}