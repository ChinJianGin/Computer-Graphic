#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 uVP;
uniform mat4 uMV;
uniform mat3 uULMM;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = uVP * uMV * vec4(vPosition, 1.0);
    texCoord = vTexCoord;
    FragPos = vec3(uMV * vec4(vPosition, 1.0));
    Normal = uULMM * vNormal;
}