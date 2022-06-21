#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBitangent;

uniform mat4 uVP;
uniform mat4 uView;
uniform mat4 uMV;
uniform vec3 particleCenter;
uniform vec2 uSize;

void main()
{
    vec3 CameraRight_world = vec3(uView[0][0], uView[1][0], uView[2][0]);
    vec3 CameraUp_world = vec3(uView[0][1], uView[1][1], uView[2][1]);
    vec3 center_worldspace = particleCenter;
    vec3 vertexPosition_world = center_worldspace + CameraRight_world * vPosition.x * uSize.x + CameraUp_world * vPosition.z * uSize.y;
    gl_Position = uVP * vec4(vertexPosition_world, 1.0);
}