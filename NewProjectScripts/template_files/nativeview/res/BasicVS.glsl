#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 uTransform;

out vec3 vertexColor;

void main()
{
    gl_Position = uTransform * vec4(position, 1.0);
    vertexColor = color;
}
