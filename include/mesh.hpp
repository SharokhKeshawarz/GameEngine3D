#pragma once

#include <iostream>
#include "glad/glad.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.hpp"

#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"

#include "texture.hpp"
#include <vector>

enum class VertexFormat : uint32_t {
    None        = 0,
    Position    = 1 << 0,
    Color       = 1 << 1,
    TexCoord    = 1 << 2,
    Normal      = 1 << 3,
    Tangent     = 1 << 4,
    Bitangent   = 1 << 5,
    BoneId      = 1 << 6,
    BoneWeight  = 1 << 7
};

inline VertexFormat operator|(VertexFormat a, VertexFormat b)
{
    return static_cast<VertexFormat>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline VertexFormat operator&(VertexFormat a, VertexFormat b)
{
    return static_cast<VertexFormat>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

inline bool HasFlag(VertexFormat mast, VertexFormat flag)
{
    return (mast & flag) != VertexFormat::None;
}

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textureCoord;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::ivec4 bonesId;
    glm::vec4 boneWeights;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices = {}, const std::vector<GLuint>& indices = {}, VertexFormat format = VertexFormat::Position, GLenum usage = GL_STATIC_DRAW);
    ~Mesh() = default;

    void Update(Shader& shader);
    void Draw() const;

    void SetTexture(Texture& texture);
    void SetTextures(const std::vector<Texture*>& textures);
    void Translate(float x, float y, float z);
    void Rotate(float angle, float x, float y, float z);
    void Scale(float x, float y, float z);

    void Destroy();

private:
    VAO vao;
    VBO vbo;
    EBO ebo;
    GLsizei indexCount = 0;
    bool useIndices = false;
    VertexFormat format;

    Texture* texture = nullptr;
    std::vector<Texture*> textures;

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

};