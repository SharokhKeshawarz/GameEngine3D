#pragma once

#include <iostream>
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
    void Update(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
    void Display();

    void Destroy();

private:
    uint32_t width, height;
    std::string title;
    GLFWwindow* renderer;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};
