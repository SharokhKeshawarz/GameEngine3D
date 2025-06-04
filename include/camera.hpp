#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "window.hpp"
#include "shader.hpp"

class Camera
{
public:
    Camera(int width, int height, glm::vec3 position);
    ~Camera() = default;

    void UpdateMatrix();
    void Matrix(Shader& shader, const std::string& uniform);
    void Inputs(Window& window);

public:
    glm::vec3 Position;
    glm::vec3 Orientation;
    glm::vec3 Up;
    glm::mat4 cameraMatrix;

    bool firstClick;
    int width, height;
    float speed;
    float sensitivity;
    float FOV;
    float nearPlane;
    float farPlane;

    double lastMouseX = 0.0;
    double lastMouseY = 0.0;

};
