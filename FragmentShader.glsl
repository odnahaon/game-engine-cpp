// OpenGL version 3.3, core
#version 330 core

// Values from vertex shaders.
//in vec3 fragmentColor;
in vec2 UV;

// Output data.
out vec3 color;

uniform sampler2D textureSampler;

void main() {
    // Colors everything according to the vertex colors.
    //color = fragmentColor;
    color = texture(textureSampler, UV).rgb;
}