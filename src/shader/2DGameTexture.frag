#version 330

out vec4 color;

in vec2 TexCoord;
in vec4 ourColor;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
void main()
{
    color = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord) , .9);
    //gl_FragColor = vec4(1.0, 0.0f, 0.0, 1.0);
}