#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 color;
out vec3 crntPos;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    crntPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = camMatrix * vec4(crntPos, 1.0);
    color = aColor;
}
