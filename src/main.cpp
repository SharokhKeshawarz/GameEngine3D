#include <unordered_map>

#include "window.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "camera.hpp"

int main()
{
    Window window(800, 600, "Game Engine");
    Shader shader("../shaders/default.vert", "../shaders/default.frag");

    std::vector<Vertex> vertices = {
            // Front face
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // Bottom-left
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, // Bottom-right
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // Top-right
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}}, // Top-left

        // Back face
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}}, // Bottom-left
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}}, // Bottom-right
        {{-0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}}, // Top-right
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}}, // Top-left

        // Left face
        {{-0.5f, -0.5f, -0.5f}, {0.2f, 0.3f, 0.4f}},
        {{-0.5f, -0.5f,  0.5f}, {0.3f, 0.4f, 0.2f}},
        {{-0.5f,  0.5f,  0.5f}, {0.4f, 0.2f, 0.3f}},
        {{-0.5f,  0.5f, -0.5f}, {0.6f, 0.6f, 0.6f}},

        // Right face
        {{ 0.5f, -0.5f,  0.5f}, {0.7f, 0.1f, 0.1f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.1f, 0.7f, 0.1f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.1f, 0.1f, 0.7f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.7f, 0.7f, 0.1f}},

        // Top face
        {{-0.5f,  0.5f,  0.5f}, {0.3f, 0.3f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.3f, 1.0f, 0.3f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.3f, 0.3f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.5f}},

        // Bottom face
        {{-0.5f, -0.5f, -0.5f}, {0.2f, 0.2f, 0.2f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.3f, 0.3f, 0.3f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.4f, 0.4f, 0.4f}},
        {{-0.5f, -0.5f,  0.5f}, {0.5f, 0.5f, 0.5f}},
    };
    std::vector<GLuint> indices = {
        // Front
        0,  1,  2,  2,  3,  0,
        // Back
        4,  5,  6,  6,  7,  4,
        // Left
        8,  9, 10, 10, 11,  8,
        // Right
        12, 13, 14, 14, 15, 12,
        // Top
        16, 17, 18, 18, 19, 16,
        // Bottom
        20, 21, 22, 22, 23, 20,
    };
    VertexFormat vertexFormat = VertexFormat::Position | VertexFormat::Color;
    
    Mesh mesh = Mesh(vertices, indices, vertexFormat, GL_STATIC_DRAW);
    mesh.Scale(2.0f, 2.0f, 2.0f);
    mesh.Translate(0.0f, 0.0f, -5.0f);

    Camera camera(window.GetWidth(), window.GetHeight(), glm::vec3(0.0f, 0.0f, 2.0f));

     while (!window.ShouldClose()) {
        shader.Bind();
        window.Update(0.1f, 0.2f, 0.3f, 1.0f);
        camera.Inputs(window);
        camera.UpdateMatrix();
        camera.Matrix(shader, "camMatrix");
        mesh.Rotate((float)glfwGetTime() * window.GetDeltaTime(), 0.0f, 0.0f, 10.0f);
        mesh.Update(shader);
        mesh.Draw();
        window.Display();
    }

    mesh.Destroy();
    shader.Destroy();
    window.Destroy();
}
