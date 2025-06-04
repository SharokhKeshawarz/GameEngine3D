#include "mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, VertexFormat format, GLenum usage)
    : format(format)
{
    std::cout << "FRON INIT" << std::endl;
    useIndices = !indices.empty();
    indexCount = useIndices
        ? static_cast<GLsizei>(indices.size())
        : static_cast<GLsizei>(vertices.size());

    vao.Bind();
    vbo.Bind();
    if (useIndices) ebo.Bind();

    vbo.BufferData(vertices, usage);
    if (useIndices) ebo.BufferData(indices, usage);
    
    int stride = sizeof(Vertex);
    int index = 0;

    if (HasFlag(format, VertexFormat::Position))
        vao.AttribPointerFloat(index++, 3, stride, offsetof(Vertex, position));
    if (HasFlag(format, VertexFormat::Color))
        vao.AttribPointerFloat(index++, 3, stride, offsetof(Vertex, color));
    if (HasFlag(format, VertexFormat::TexCoord))
        vao.AttribPointerFloat(index++, 2, stride, offsetof(Vertex, textureCoord));
    if (HasFlag(format, VertexFormat::Normal))
        vao.AttribPointerFloat(index++, 3, stride, offsetof(Vertex, normal));
    if (HasFlag(format, VertexFormat::Tangent))
        vao.AttribPointerFloat(index++, 3, stride, offsetof(Vertex, tangent));
    if (HasFlag(format, VertexFormat::Bitangent))
        vao.AttribPointerFloat(index++, 3, stride, offsetof(Vertex, bitangent));
    if (HasFlag(format, VertexFormat::BoneId))
        vao.AttribPointerInt(index++, 4, stride, offsetof(Vertex, bonesId));
    if (HasFlag(format, VertexFormat::BoneWeight))
        vao.AttribPointerFloat(index++, 4, stride, offsetof(Vertex, boneWeights));

    vao.Unbind();
}

void Mesh::Update(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);

    shader.SetMat4("model", GL_FALSE, glm::value_ptr(model));
}

void Mesh::Draw() const
{
    vao.Bind();

    useIndices
        ? glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr)
        : glDrawArrays(GL_TRIANGLES, 0, indexCount);
    
    vao.Unbind();
}

void Mesh::Translate(float x, float y, float z)
{
    position += glm::vec3(x, y, z);
}

void Mesh::Rotate(float angle, float x, float y, float z)
{
    rotation += glm::vec3(x * angle, y * angle, z * angle);
}

void Mesh::Scale(float x, float y, float z)
{
    scale *= glm::vec3(x, y, z);
}

void Mesh::Destroy()
{
    vao.Destroy();
    vbo.Destroy();
    ebo.Destroy();
}
