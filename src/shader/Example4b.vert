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

    mat4 tm = mat4
    (
          1,  0,  0, 0,
          0,  1,  0, 0,
          0,  0,  1, 0,
        .5f, .5f, 0, 1
    );

    gl_Position = tm * rz * vec4(vPosition.xyz * .25f, 1.f);
    color = vec4( vColor, 1.f);
}