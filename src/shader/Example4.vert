#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;

out vec4 color;

void main(){
    gl_Position = vec4(vPosition, 1.f);
    if(vPosition.x > 0 && vPosition.y > 0)
    {
        color = vec4(1.f, 0.f, 1.f, 1.f);    
    }
    else
    {
        color = vec4(.0f, 1.f, 1.f, 1.f);    
    }
    //color = vec4( vColor, 1.f);
}