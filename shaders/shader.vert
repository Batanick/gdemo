#version 330 core

uniform mat4 MVP;

in vec3 vCol;
in vec3 vPos;

out vec3 vColor;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    vColor = vCol;
}
