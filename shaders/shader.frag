#version 330 core

in vec3 fColor;
in vec3 fNorm;

out vec4 color;

void main()
{
    color = vec4(fColor * fNorm, 1.0);
}