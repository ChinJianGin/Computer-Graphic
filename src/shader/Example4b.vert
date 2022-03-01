#version 330
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;

out vec4 color;

uniform float angle;

void main(){
    float a = radians(angle);
    float x = cos(a);
    float y = sin(a);

    mat4 rz = mat4
    ( 
          x,   y, 0.f, 0.f,
         -y,   x, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );

    gl_Position = rz * vec4(vPosition, 1.f);
    color = vec4( vColor, 1.f);
}