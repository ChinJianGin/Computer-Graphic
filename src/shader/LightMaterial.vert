#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBitangent;

uniform mat4 uVP;
uniform mat4 uMV;
uniform mat3 uULMM;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;
out mat3 TBN;

void main()
{
    FragPos = vec3(uMV * vec4(vPosition, 1.0));
    texCoord = vTexCoord;
    Normal = uULMM * vNormal;

    vec3 T = normalize(vec3(uMV * vec4(vTangent, 0.0)));
    // vec3 B = normalize(vec3(uMV * vec4(vBitangent, 0.0)));
    vec3 N = normalize(vec3(uMV * vec4(vNormal, 0.0)));
    // TBN = mat3(T, B, N);
    // vec3 T = normalize(Normal * vTangent);
    // vec3 N = normalize(Normal * vNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    // TBN = transpose(mat3(T, B, N));
    TBN = mat3(T, B, N);
    gl_Position = uVP * uMV * vec4(vPosition, 1.0);
}