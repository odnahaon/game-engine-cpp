// OpenGL version 3.3, core.
#version 330 core

// Input data.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 textureCoordIn;

out vec2 textureCoord;
out vec3 fragmentColor;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;
    fragmentColor = vertexColor;
    textureCoord = textureCoordIn;
}