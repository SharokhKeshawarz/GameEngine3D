#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out vec3 color;
out vec3 normal;
out vec3 FragPos;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = camMatrix * vec4(FragPos, 1.0);
    color = aColor;
    texCoord = aTexCoord;
}
