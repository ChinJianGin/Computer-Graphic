#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 uVP;
uniform mat4 uMV;

void main()
{
    gl_Position = uVP * uMV * vec4(vPosition, 1.0);
}