// OpenGL version 3.3, core
#version 330 core

// Values from vertex shaders
in vec3 fragmentColor;

// Output data.
out vec3 color;

void main() {
    // Colors everything according to the vertex colors.
    color = fragmentColor;
}