#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 uVP;
uniform mat4 uMV;

out vec3 color;
out vec2 texCoord;

void main()
{
    gl_Position = uVP * uMV * vec4(vPosition, 1.0);
    color = vColor;
    texCoord = vTexCoord;
}