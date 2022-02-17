// OpenGL version 3.3, core
#version 330 core

// Values from vertex shaders
in vec3 fragmentColor;
in vec2 textureCoord;

// Output data.
//out vec3 color;
out vec4 color;

uniform sampler2D tex;

void main() {
    // Colors everything according to the vertex colors.
    //color = fragmentColor;
    color = texture(tex, textureCoord) * vec4(fragmentColor, 1.0);
}