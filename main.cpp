// Standard includes
#include <stdio.h>
#include <stdlib.h>

// GLEW. Extension loading.
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW. Handles window and keyboard.
#include <GLFW/glfw3.h>
// Window declaration.
GLFWwindow* window;

// GLM. 3D math.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// The shader file I wrote.
#include <loadShader.hpp>

int main() {
    // Initialize GLFW and check to make sure it is initialized properly.
    glfwInit();
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
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
    window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.");
        getchar();
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

    // Dark blue background.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Depth testing.
    glEnable(GL_DEPTH_TEST);
    // Nearest to camera only.
    glDepthFunc(GL_LESS);

    // Creating the Vertex Array Object (VAO).
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Load the shaders.
    GLuint programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");

    // MVP uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Matrix for projection.
    // 45° FOV, 4:3, display range 0.1 to 100.
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Matrix for camera.
    // Camera located at (4,3,-3) world space, looks at (0,0,0), right side up ((0,-1,0) upside down).
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // Matrix for model.
    // AKA identity matrix.
    glm::mat4 model = glm::mat4(1.0f);
    // ModelViewProjection to multiply the matrices.
    // Keep in mind that matrix multiplication will reverse the order.
    glm::mat4 MVP = projection * view * model;

    // Array of vectors. These represent 3 vertices: bottom left, bottom right, and middle top.
    static const GLfloat g_vertex_buffer_data[] = {
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f
    };

    // Colors for the vertices.
    static const GLfloat g_color_buffer_data[] = {
	    0.583f,  0.771f,  0.014f,
	    0.609f,  0.115f,  0.436f,
	    0.327f,  0.483f,  0.844f,
	    0.822f,  0.569f,  0.201f,
	    0.435f,  0.602f,  0.223f,
	    0.310f,  0.747f,  0.185f,
	    0.597f,  0.770f,  0.761f,
	    0.559f,  0.436f,  0.730f,
	    0.359f,  0.583f,  0.152f,
	    0.483f,  0.596f,  0.789f,
	    0.559f,  0.861f,  0.639f,
	    0.195f,  0.548f,  0.859f,
	    0.014f,  0.184f,  0.576f,
	    0.771f,  0.328f,  0.970f,
	    0.406f,  0.615f,  0.116f,
	    0.676f,  0.977f,  0.133f,
	    0.971f,  0.572f,  0.833f,
	    0.140f,  0.616f,  0.489f,
	    0.997f,  0.513f,  0.064f,
	    0.945f,  0.719f,  0.592f,
	    0.543f,  0.021f,  0.978f,
	    0.279f,  0.317f,  0.505f,
	    0.167f,  0.620f,  0.077f,
	    0.347f,  0.857f,  0.137f,
	    0.055f,  0.953f,  0.042f,
	    0.714f,  0.505f,  0.345f,
	    0.783f,  0.290f,  0.734f,
	    0.722f,  0.645f,  0.174f,
	    0.302f,  0.455f,  0.848f,
	    0.225f,  0.587f,  0.040f,
	    0.517f,  0.713f,  0.338f,
	    0.053f,  0.959f,  0.120f,
	    0.393f,  0.621f,  0.362f,
	    0.673f,  0.211f,  0.457f,
	    0.820f,  0.883f,  0.371f,
	    0.982f,  0.099f,  0.879f
    };

    // Buffers for vertices.
    GLuint vertexBuffer;
    // 1 buffer and put result in vertexBuffer, then bind it.
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Hand our vertex data to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Buffers for colors.
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // do while loop keeps the window open until the ESCAPE key is pressed.
    do {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader.
        glUseProgram(programID);

        // Sends the MVP uniform.
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Vertex buffer.
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Color buffer.
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Draw.
        // 0: starting vertex, 3: total of vertices.
        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        // Disable the vertices.
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swapping buffers and stuff.
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    
    // Cleanup. Always good to free up resources.
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Cleans up everything so the allocated resources are released.
    glfwTerminate();
    return 0;
}