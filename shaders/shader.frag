#version 330 core

uniform vec3 lightDirView;

in vec3 fColor;
in vec3 fNormalView;
in vec3 posView;

const vec3 ambientColor = vec3(0.1, 0.0, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);
const float shininess = 0.0;
const float screenGamma = 2.2;

out vec4 color;

void main()
{
    vec3 normal = normalize(fNormalView);

    float lambertian = max(dot(lightDirView, normal), 0.0);
    float specular = 0.0;

    if(lambertian > 0.0) {
        vec3 viewDir = normalize(-posView);

        vec3 halfDir = normalize(lightDirView + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, shininess);
    }

    vec3 colorLinear = ambientColor + lambertian * fColor + specular * specColor;
    vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));
    color = vec4(colorGammaCorrected, 1.0);
}