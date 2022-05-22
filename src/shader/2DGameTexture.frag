#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform int HaveTex = 1;
uniform float U_a = 1.0;

void main()
{
    // FragColor = vec4(texCoord, 0.0, 1.0);
    if(HaveTex == 1)
    {
        FragColor = texture(tex0, texCoord);
        FragColor.a *= U_a;
    }
    else
    {
        FragColor = vec4(color, 1.0);
    }
}