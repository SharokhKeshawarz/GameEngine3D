#pragma once

#include <glad/glad.h>
#include <vector>

class VBO
{
public:
    VBO();
    ~VBO() = default;

    void Bind();
    void Unbind();
    
    template <typename T>
    void BufferData(const std::vector<T>& data, GLenum usage=GL_STATIC_DRAW)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), usage);
    }

    void Destroy();

private:
    GLuint id;
};
