#pragma once

#include <glad/glad.h>
#include "vbo.hpp"

class VAO
{
public:
    VAO();
    ~VAO() = default;

    void Bind() const;
    void Unbind() const;
    void AttribPointerFloat(GLint index, GLint size, GLsizei stride, size_t pointer);
    void AttribPointerInt(GLint index, GLint size, GLsizei stride, size_t pointer);
    void Destroy();
private:
    GLuint id = 0;
};
