#include "camera.hpp"

Camera::Camera(int width, int height, glm::vec3 position)
{
    firstClick = true;
    speed = 25.0f;
    sensitivity = 100.0f;
    Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraMatrix = glm::mat4(1.0f);
    this->width = width;
    this->height = height;
    Position = position;
    FOV = 45.0f;
    nearPlane = 1.0f;
    farPlane = 100.0f;
}

void Camera::UpdateMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOV), static_cast<float>(width)/static_cast<float>(height), nearPlane, farPlane);
    cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const std::string& uniform)
{
    shader.SetMat4(uniform, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(Window& window)
{
    float deltaTime = window.GetDeltaTime();
    float velocity;

    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        velocity = (speed * 2.0f) * deltaTime;
    else
        velocity = speed * deltaTime;

    // Movement
    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_W) == GLFW_PRESS)
        Position += velocity * Orientation;
    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_A) == GLFW_PRESS)
        Position += velocity * -glm::normalize(glm::cross(Orientation, Up));
    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_S) == GLFW_PRESS)
        Position += velocity * -Orientation;
    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_D) == GLFW_PRESS)
        Position += velocity * glm::normalize(glm::cross(Orientation, Up));
    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_SPACE) == GLFW_PRESS)
        Position += velocity * Up;
    if (glfwGetKey(window.GetRenderer(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Position += velocity * -Up;

    // Mouse input
    if (glfwGetMouseButton(window.GetRenderer(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window.GetRenderer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        double mouseX, mouseY;
        glfwGetCursorPos(window.GetRenderer(), &mouseX, &mouseY);

        if (firstClick) {
            lastMouseX = mouseX;
            lastMouseY = mouseY;
            firstClick = false;
        }

        float deltaX = static_cast<float>(mouseX - lastMouseX);
        float deltaY = static_cast<float>(mouseY - lastMouseY);

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        float rotX = sensitivity * deltaY / height;
        float rotY = sensitivity * deltaX / width;

        glm::vec3 right = glm::normalize(glm::cross(Orientation, Up));
        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), right);

        if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            Orientation = newOrientation;

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
    }
    else {
        glfwSetInputMode(window.GetRenderer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
