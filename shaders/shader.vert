#version 330 core

uniform mat4 MVP;
uniform mat4 view;
//uniform mat4 projection;

uniform vec3 lightDirView;

in vec3 vColor;
in vec3 vNorm;
in vec3 vPos;

out vec3 fColor;
out vec3 fNormalView;
out vec3 posView;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);

    posView = (view * gl_Position).xyz;
    fColor = vColor;
    fNormalView = (view * vec4(vNorm, 0.0)).xyz;
}
