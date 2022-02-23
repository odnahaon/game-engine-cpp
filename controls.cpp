#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::mat4 getViewMatrix() {
    return viewMatrix;
}

glm::mat4 getProjectionMatrix() {
    return projectionMatrix;
}

glm::vec3 position = glm::vec3(0, 0, 5);
float horizAngle = 3.14f;
float vertiAngle = 0.0f;
float initFOV = 70.0f;
float speed = 3.0f;
float mouseSpeed = 0.1f;
int width = 800;
int height = 600;
float FOV;
static double lastTime = glfwGetTime();

void computeMatricesFromInputs() {

    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    glfwSetCursorPos(window, width / static_cast<double>(2), height / static_cast<double>(2));

    horizAngle += mouseSpeed * deltaTime * float(width / static_cast<double>(2) - xPos);
    vertiAngle += mouseSpeed * deltaTime * float(height / static_cast<double>(2) - yPos);

    glm::vec3 direction(cos(vertiAngle) * sin(horizAngle), sin(vertiAngle), cos(vertiAngle) * cos(horizAngle));

    glm::vec3 directionNoUp(cos(vertiAngle) * sin(horizAngle), 0, cos(vertiAngle) * cos(horizAngle));

    glm::vec3 right = glm::vec3(sin(horizAngle - 3.14f / 2.0f), 0, cos(horizAngle - 3.14f / 2.0f));

    glm::vec3 up = glm::cross(right, direction);

    glm::vec3 forward = glm::cross(right, glm::cross(right, directionNoUp));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position -= forward * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position += forward * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += up * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= up * deltaTime * speed;
    }

    FOV = initFOV;

    projectionMatrix = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(position, position + direction, up);

    lastTime = currentTime;
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    FOV -= (float)yOffset;
    if (FOV < 30.0f) {
        FOV = 30.0f;
    }
    if (FOV > 110.0f) {
        FOV = 110.0f;
    }
}