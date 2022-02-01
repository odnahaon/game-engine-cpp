// Standard includes
#include <stdio.h>
#include <stdlib.h>

// GLEW. The magic.
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW. Handles window and keyboard.
#include <GLFW/glfw3.h>

// GLM. 3D math.
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform.hpp>
using namespace glm;

// The shader file I wrote.
#include <loadShader.hpp>

int main() {
    // Initialize GLFW and check to make sure it is initialized properly.
    glfwInit();
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Set antialiasing to 4x.
    glfwWindowHint(GLFW_SAMPLES, 4);
    // OpenGL 3.3 needed.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Cross-platform compatibility with MacOS.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Use the new OpenGL.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open the window that is 800x600 with the title "Game Engine"
    GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return -1;
    }

    // Initialize GLEW
    glfwMakeContextCurrent(window);
    // Needed because of the line glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);.
    glewExperimental = true;
    // Error checking.
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Make sure keys are captured.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Creating the Vertex Array Object (VAO).
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Array of vectors. These represent 3 vertices: bottom left, bottom right, and middle top.
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    // Buffers.
    GLuint vertexBuffer;
    // 1 buffer and put result in vertexBuffer, then bind it.
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Hand our vertex data to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");
    // do while loop keeps the window open until the ESCAPE key is pressed.
    do {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader.
        glUseProgram(programID);

        // Vertex buffer.
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Draw.
        // 0: starting vertex, 3: total of vertices.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        // Swapping buffers and stuff.
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    
    // Cleans up everything so the allocated resources are released.
    glfwTerminate();
    return 0;
}