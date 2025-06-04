#include "window.hpp"

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    this->width = width;
    this->height = height;
    this->title = title;
    
    if (!glfwInit()) {
        std::cout << "FAILED TO INIT GLFW" << std::endl;
        exit(84);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->renderer = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!this->renderer) {
        std::cout << "FAILED TO INIT WINDOW" << std::endl;
        exit(84);
    }
    glfwMakeContextCurrent(this->renderer);
    glfwSwapInterval(0);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INIT GLAD" << std::endl;
        exit(84);
    }
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

uint32_t Window::GetWidth() const
{
    return this->width;
}

uint32_t Window::GetHeight() const
{
    return this->height;
}

std::string Window::GetTitle() const
{
    return this->title;
}

GLFWwindow* Window::GetRenderer() const
{
    return this->renderer;
}

float Window::GetDeltaTime() const
{
    return deltaTime;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(this->renderer);
}

void Window::Update(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Display()
{
    glfwSwapBuffers(this->renderer);
    glfwPollEvents();
}

void Window::Destroy()
{
    glfwDestroyWindow(this->renderer);
    this->renderer = nullptr;
    glfwTerminate();
}
