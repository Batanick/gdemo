#version 330 core

uniform mat4 MVP;

in vec3 vColor;
in vec3 vNorm;
in vec3 vPos;

out vec3 fNorm;
out vec3 fColor;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    fColor = vColor;
    fNorm = vNorm;
}
