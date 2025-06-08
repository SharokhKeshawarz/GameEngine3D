#include "texture.hpp"

Texture::Texture(Shader& shader, const std::string& name, const std::string& textureFilePath, int slot)
{
    filePath = textureFilePath;
    this->slot = slot;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channel, 0);
    if (!data) {
        std::cerr << "Failed to open textrue: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum internalFormat;
    GLenum dataFormat;

    if (channel == 1)
        internalFormat = dataFormat = GL_RED;
    else if (channel == 3)
        internalFormat = dataFormat = GL_RGB;
    else if (channel == 4)
        internalFormat = dataFormat = GL_RGBA;
    else {
        std::cerr << "Unsupported channel count: " << channel << std::endl;
        stbi_image_free(data);
        exit(EXIT_FAILURE);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    shader.Bind();
    shader.SetInt(name, slot);
    shader.Unbind();
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Destroy()
{
    glDeleteTextures(1, &id);
}
