#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 uVP;
uniform mat4 uMV;
uniform vec4 uColor = vec4(0.f, 0.f, 0.f, 0.f);

out vec4 color;

void main(){
    gl_Position = uVP * uMV *vec4(vPosition, 1.0);
    if(uColor != vec4(0, 0, 0, 0))
    {
        if(vPosition.x > 0)
        color = uColor;
        else
        color = vec4(.8, .12, .8, 1.0);
    }
    else
    {
        color = vec4(vColor , 1);
    }
}