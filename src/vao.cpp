#include "vao.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::Bind() const
{
    glBindVertexArray(id);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::AttribPointerFloat(GLint index, GLint size, GLsizei stride, size_t pointer)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(pointer));
    glEnableVertexAttribArray(index);
}

void VAO::AttribPointerInt(GLint index, GLint size, GLsizei stride, size_t pointer)
{
    glVertexAttribIPointer(index, size, GL_INT, stride, reinterpret_cast<void*>(pointer));
    glEnableVertexAttribArray(index);
}

void VAO::Destroy()
{
    glDeleteVertexArrays(1, &id);
}
