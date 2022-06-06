#version 330 core
layout (location = 0) in vec3 vPosition;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = vPosition;
    vec4 pos = projection * view * vec4(vPosition, 1.0);
    gl_Position = pos.xyww;
}