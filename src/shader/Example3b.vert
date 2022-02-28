#version 330
layout (location = 0) in vec4 vPosition;

out vec4 color;

void main()
{
    gl_Position = vPosition;
    color = vec4( (1.f + vPosition.x) / 2.f, (1.f + vPosition.y) / 2.f, (1.f + vPosition.z) / 2.f, 1.f);
}