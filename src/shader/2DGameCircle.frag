#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform float fade = 0.005;
uniform float thickness = 1.0;
uniform sampler2D tex0;

void main()
{
    //FragColor = texture(tex0, texCoord) * vec4(color, 1.0);
    vec2 uv = (texCoord * 2.0) - 1.0;
    float distance = 1.0 - dot(uv, uv);
    float circleAlpha = smoothstep(0.0, fade, distance);

    circleAlpha *= smoothstep(thickness + fade, thickness, distance);

    FragColor = texture(tex0, texCoord);
    FragColor.a *= circleAlpha;

}