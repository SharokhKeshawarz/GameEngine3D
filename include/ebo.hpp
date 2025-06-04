#pragma once

#include "glad/glad.h"
#include <vector>

class EBO
{
public:
    EBO();
    ~EBO() = default;

    void Bind();
    void Unbind();
    void BufferData(const std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW);
    void Destroy();

private:
    GLuint id;
};
