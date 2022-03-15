// OpenGL version 3.3, core
#version 330 core

// Values from vertex shaders
in vec2 UV;
in vec3 position_worldspace;
in vec3 normal_cameraspace;
in vec3 eyeDirection_cameraspace;
in vec3 lightDirection_cameraspace;

// Output data.
out vec3 color;

uniform sampler2D tex;
uniform mat4 MV;
uniform vec3 lightPosition_worldspace;
uniform vec3 lightColor;
uniform float lightPower;

// Data that will be passed from the program
uniform vec3 materialDiffuseColor;
uniform vec3 materialAmbientColor;
uniform vec3 MaterialSpecularColor;

void main() {
    vec3 lightColor = vec3(2, 2, 2);
    float lightPower = 500.0f;

    //vec3 materialDiffuseColor = texture(tex, UV).rgb;
    //vec3 materialAmbientColor = vec3(0.8, 0.8, 0.8) * materialDiffuseColor;
    //vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3);

    float distance = length(lightPosition_worldspace - position_worldspace);
    
    // Normal of fragment in camera space.
    vec3 n = normalize(normal_cameraspace);
    // Direction of light.
    vec3 l = normalize(lightDirection_cameraspace);

    float cosTheta = clamp(dot(n, l), 0, 1);
    
    vec3 E = normalize(eyeDirection_cameraspace);
    vec3 R = reflect(-l, n);
    float cosAlpha = clamp(dot(E, R), 0, 1);

    color = materialAmbientColor + materialDiffuseColor * lightColor * lightPower * cosTheta / (distance * distance) + materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (distance * distance);
}