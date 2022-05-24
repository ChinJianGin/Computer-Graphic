#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D tex0;
uniform bool HaveTex = true;
uniform vec4 uColor;
uniform float U_a = 1.0;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    if(HaveTex)
    {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        float ambientStrenth = 0.5;
        vec3 ambient = ambientStrenth * lightColor;
        FragColor = texture(tex0, texCoord) * vec4(ambient + diffuse, 1.0);
        FragColor.a *= U_a;
    }
    else
    {
        FragColor = uColor;
    }
}