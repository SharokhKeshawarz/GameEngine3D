#pragma once

#include <unordered_map>
#include "window.hpp"
#include "shader.hpp"

class App
{
public:
    App() = default;
    ~App() = default;

    void Init();
    void Run();
    void Destroy();

private:
    std::shared_ptr<Window> window;
    std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaders;
};
