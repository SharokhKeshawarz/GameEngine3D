#pragma once

#include <iostream>
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "shader.hpp"

class Texture
{
public:
    Texture(Shader& shader, const std::string& name, const std::string& textureFilePath, int slot);
    ~Texture() = default;

    void Bind();
    void Unbind();

    void Destroy();

private:
    GLuint id;
    int width, height, channel;
    std::string filePath;
    int slot;
};
