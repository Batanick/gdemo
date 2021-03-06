#include "Camera.h"
#include "logging.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

static const float CAMERA_MOVE_SPEED = 10.0f;
static const float CAMERA_ROTATION_SPEED = 0.005f;
static const float PI_2 = 3.1415926f / 2;

Camera::Camera() {
    horizontalAngle = 0.0f;
    verticalAngle = 0.0f;
    position = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::onBeforeRender(GLFWwindow *const window, double deltaTime) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED) != GL_TRUE) {
        return;
    }

    double mouseXPos, mouseYPos;
    glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
    int windowHeight, windowWidth;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    horizontalAngle += CAMERA_ROTATION_SPEED * float(windowWidth / 2 - mouseXPos);
    verticalAngle += CAMERA_ROTATION_SPEED * float(windowHeight / 2 - mouseYPos);

    verticalAngle = std::max(-PI_2, verticalAngle);
    verticalAngle = std::min(PI_2, verticalAngle);

    const glm::vec3 direction = getDirection();
    const glm::vec3 right = getRight();

    // Forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * (float) deltaTime * CAMERA_MOVE_SPEED;
    }
    // Backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * (float) deltaTime * CAMERA_MOVE_SPEED;
    }
    // Right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * (float) deltaTime * CAMERA_MOVE_SPEED;
    }
    // Left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * (float) deltaTime * CAMERA_MOVE_SPEED;
    }

    //Switching polygon draw mode
    static bool buttonUp = true;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (buttonUp) {
            GLint currentMode[2]; //front and back value
            glGetIntegerv(GL_POLYGON_MODE, &currentMode[0]);
            glPolygonMode(GL_FRONT_AND_BACK, currentMode[0] == GL_LINE ? GL_FILL : GL_LINE);
            buttonUp = false;
        }
    }
    else {
        buttonUp = true;
    }
}

glm::vec3 Camera::getRight() {
    return glm::vec3(
            sin(horizontalAngle - 3.14f / 2.0f),
            0,
            cos(horizontalAngle - 3.14f / 2.0f)
    );
}

glm::vec3 Camera::getUp() {
    return glm::cross(getRight(), getDirection());
}

glm::vec3 Camera::getDirection() {
    return glm::vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
    );
}

glm::vec3 Camera::getPosition() {
    return position;
}
