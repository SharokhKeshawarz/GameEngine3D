#include "app.hpp"

void App::Init()
{
    window = std::make_shared<Window>(800, 600, "Game Engine");
    shaders[ShaderType::Basic] = std::make_shared<Shader>("../shaders/default.vert", "../shaders/default.frag");
}

void App::Run()
{
    while (!window->ShouldClose()) {
        shaders[ShaderType::Basic]->Bind();
        window->Update(0.1f, 0.2f, 0.3f, 1.0f);
        
        window->Display();
    }
}

void App::Destroy()
{
    window->Destroy();
    shaders[ShaderType::Basic]->Destroy();
}
