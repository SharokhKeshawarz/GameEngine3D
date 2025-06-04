#include "ebo.hpp"

EBO::EBO()
{
    glGenBuffers(1, &id);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::BufferData(const std::vector<GLuint>& indices, GLenum usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), usage);
}

void EBO::Destroy()
{
    glDeleteBuffers(1, &id);
}
