#include <unordered_map>

#include "window.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "texture.hpp"

int main()
{
    Window window(800, 600, "Game Engine");

    Shader shader("../shaders/default.vert", "../shaders/default.frag");

    std::vector<Vertex> vertices = {
        // FRONT (+Z)
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

        // BACK (-Z)
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

        // LEFT (-X)
        {{-0.5f, -0.5f, -0.5f}, {0.2f, 0.3f, 0.4f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.3f, 0.4f, 0.2f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.4f, 0.2f, 0.3f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.6f, 0.6f, 0.6f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

        // RIGHT (+X)
        {{ 0.5f, -0.5f,  0.5f}, {0.7f, 0.1f, 0.1f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.1f, 0.7f, 0.1f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.1f, 0.1f, 0.7f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.7f, 0.7f, 0.1f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

        // TOP (+Y)
        {{-0.5f,  0.5f,  0.5f}, {0.3f, 0.3f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.3f, 1.0f, 0.3f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.3f, 0.3f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

        // BOTTOM (-Y)
        {{-0.5f, -0.5f, -0.5f}, {0.2f, 0.2f, 0.2f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.3f, 0.3f, 0.3f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.4f, 0.4f, 0.4f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    };


    std::vector<GLuint> indices = {
        0,  1,  2,  2,  3,  0,
        4,  5,  6,  6,  7,  4,
        8,  9, 10, 10, 11,  8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20,
    };

    Texture texture0(shader, "texture0", "../assets/wall.jpg", 0);
    Texture texture1(shader, "texture1", "../assets/face.png", 1);
    std::vector<Texture*> textures = {
        &texture0,
        &texture1
    };

    Mesh cube = Mesh(vertices, indices, VertexFormat::Position | VertexFormat::Color | VertexFormat::TexCoord | VertexFormat::Normal, GL_STATIC_DRAW);
    cube.SetTextures(textures);

    Camera camera(window.GetWidth(), window.GetHeight(), glm::vec3(0.0f, 0.0f, 2.0f));

    while (!window.ShouldClose()) {
        camera.Update(window);
        window.Update(0.1f, 0.2f, 0.3f, 1.0f);
        
        // CUBE
        shader.Bind();
        camera.Matrix(shader, "camMatrix");
        cube.Update(shader);
        cube.Draw();

        window.Display();
        shader.Unbind();
    }

    cube.Destroy();
    shader.Destroy();
    window.Destroy();
}
