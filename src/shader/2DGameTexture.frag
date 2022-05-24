#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform bool HaveTex = true;
uniform vec4 uColor;
uniform float U_a = 1.0;

void main()
{
    if(HaveTex)
    {
        FragColor = texture(tex0, texCoord);
        FragColor.a *= U_a;
    }
    else
    {
        FragColor = uColor;
    }
}