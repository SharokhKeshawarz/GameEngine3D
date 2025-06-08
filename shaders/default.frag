#version 460 core
out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

in vec3 color;
in vec3 normal;
in vec3 FragPos;
in vec2 texCoord;

void main()
{
    FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.5) * vec4(color, 1.0);
}
