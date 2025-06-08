#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(uint32_t width, uint32_t height, const std::string& title);
    ~Window() = default;

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    std::string GetTitle() const;
    GLFWwindow* GetRenderer() const;
    float GetDeltaTime() const;
    
    bool ShouldClose() const;
    void Update(float r, float g, float b, float a);
    void Display();

    void Destroy();

private:
    uint32_t width, height;
    std::string title;
    GLFWwindow* renderer;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float fpsTimer = 0.0f;
    int frameCount = 0;
};
