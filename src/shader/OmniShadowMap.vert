#version 330 core
layout (location = 0) in vec3 vPosition;

uniform mat4 uMV;

void main()
{
    gl_Position = uMV * vec4(vPosition, 1.0);
}