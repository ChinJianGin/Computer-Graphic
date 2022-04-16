#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 uVP;
uniform mat4 uMV;
uniform vec4 uColor;

out vec2  TexCoord;
out vec4 ourColor;
void main(){
    TexCoord = vTexCoord;
    ourColor = uColor;
    gl_Position = uVP * uMV *vec4(vPosition, 1.0);
    //gl_Position = vec4(vPosition, 1.0);
}