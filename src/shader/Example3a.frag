#version 330

in vec4 color;

void main()
{
    gl_FragColor = color;
    //gl_FragColor = vec4(1.0, 0.0f, 0.0, 1.0);
}