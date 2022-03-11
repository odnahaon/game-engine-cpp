// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

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

// The custom files I wrote.
#include "loadShader.hpp"
#include "controls.hpp"
#include "loadTextures.hpp"
#include "loadObj.hpp"
#include "loadDDS.hpp"
#include "vboIndexer.hpp"

int main() {
    // Width of the window.
    int width = 800;
    // Height of the window.
    int height = 600;

    // Initialize GLFW and check to make sure it is initialized properly.
    glfwInit();
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        //getchar();
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
    window = glfwCreateWindow(width, height, "Game Engine", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        //getchar();
        glfwTerminate();
        return -1;
    }

    // Initialize GLEW
    glfwMakeContextCurrent(window);
    // Needed because of the line glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);.
    glewExperimental = true;
    // Error checking.
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW.\n");
        return -1;
    }

    // Make sure keys are captured.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Unlimited mouse movement and hid the mouse.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwPollEvents();

    // Center the cursor on the screen.
    glfwSetCursorPos(window, static_cast<double>(width) / 2, static_cast<double>(height) / 2);

    // Dark blue background.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Depth testing.
    glEnable(GL_DEPTH_TEST);
    // Depth test for nearest to camera only.
    glDepthFunc(GL_LESS);

    // Backface culling. Disables sides not towards camera.
    glEnable(GL_CULL_FACE);

    // Creating the Vertex Array Object (VAO).
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Load the GLSL shaders.
    GLuint programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");

    // Handle for the MVP (ModelViewProjection) uniform.
    GLuint matrixID = glGetUniformLocation(programID, "MVP");
    GLuint viewMatrixID = glGetUniformLocation(programID, "V");
    GLuint modelMatrixID = glGetUniformLocation(programID, "M");

    /* This is now unused due to implementation of controls. Use this code if the camera needs to be locked in place.
    // Matrix for projection.
    // 45° FOV, 4:3, display range 0.1 to 100.
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Matrix for camera.
    // Camera located at (4,3,-3) world space, looks at (0,0,0), right side up ((0,-1,0) upside down).
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // Matrix for model.
    // AKA identity matrix.
    glm::mat4 model = glm::mat4(1.0f);
    // ModelViewProjection to multiply the matrices.
    // Keep in mind that matrix multiplication will reverse the order.
    glm::mat4 MVP = projection * view * model;
    */

    /* This code is now unused due to texture and model loading. Reuse to create a rainbow cube.
    // Array of vectors. These represent vertices.
    static const GLfloat g_vertex_buffer_data[] = {

        // 1; Left side; bottom front
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,

        // 2; Back side; top right
	    1.0f, 1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,

        // 3; Bottom side; front left
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,

        // 4; Back side; bottom left
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,

        // 5; Left side; top back
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,

        // 6; Bottom side; back right
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,

        // 7; Front side; left bottom
	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,

        // 8; Right side; top back
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,

        // 9; Right side; front bottom
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,

        // 10; Top side; back right
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,

        // 11; Top side; front left
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,

        // 12; Front side; top right
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f
    };

    // Colors for the vertices.
    static const GLfloat g_color_buffer_data[] = {
        
        // 1
	    1.000f,  0.000f,  0.000f,
        0.000f,  1.000f,  0.000f,
        0.000f,  0.000f,  1.000f,

        // 2
	    1.000f,  0.000f,  0.000f,
	    1.000f,  0.000f,  0.000f,
	    0.000f,  1.000f,  0.000f,

        // 3
	    1.000f,  0.000f,  0.000f,
	    1.000f,  0.000f,  0.000f,
	    0.000f,  0.000f,  1.000f,
        
        // 4
	    1.000f,  0.000f,  0.000f,
	    0.000f,  0.000f,  1.000f,
	    1.000f,  0.000f,  0.000f,
        
        // 5
	    1.000f,  0.000f,  0.000f,
	    0.000f,  0.000f,  1.000f,
	    0.000f,  1.000f,  0.000f,
        
        // 6
	    1.000f,  0.000f,  0.000f,
	    0.000f,  1.000f,  0.000f,
	    1.000f,  0.000f,  0.000f,
        
        // 7
	    0.000f,  0.000f,  1.000f,
	    0.000f,  1.000f,  0.000f,
	    1.000f,  0.000f,  0.000f,
        
        // 8
	    0.000f,  1.000f,  0.000f,
	    0.000f,  0.000f,  1.000f,
	    1.000f,  0.000f,  0.000f,
        
        // 9
	    0.000f,  0.000f,  1.000f,
	    0.000f,  1.000f,  0.000f,
	    1.000f,  0.000f,  0.000f,
        
        // 10
	    0.000f,  1.000f,  0.000f,
	    1.000f,  0.000f,  0.000f,
	    0.000f,  1.000f,  0.000f,
        
        // 11
	    0.000f,  1.000f,  0.000f,
	    0.000f,  1.000f,  0.000f,
	    0.000f,  0.000f,  1.000f,
        
        // 12
	    0.000f,  1.000f,  0.000f,
	    0.000f,  0.000f,  1.000f,
	    1.000f,  0.000f,  0.000f
    };*/

    // Load textures.
    GLuint texture = loadDDS("resources\\cobblestone_DXT5_MIPS.DDS");
    //GLuint texture = loadDDS("resources\\rainbow.DDS");
    GLuint textureID = glGetUniformLocation(programID, "tex");

    // Texture related.
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Load models.
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    bool res = loadObj("bigger_cube.obj", vertices, uvs, normals);
    //bool res = loadObj("cube.obj", vertices, uvs, normals);
    //bool res = loadObj("pentakis_icosidodecahedron.obj", vertices, uvs, normals);
    //bool res = loadObj("sphere.obj", vertices, uvs, normals);
    //bool res = loadObj("plane.obj", vertices, uvs, normals);
    //bool res = loadObj("cone.obj", vertices, uvs, normals);
    //bool res = loadObj("cylinder.obj", vertices, uvs, normals);
    //bool res = loadObj("donut.obj", vertices, uvs, normals);
    //bool res = loadObj("monke.obj", vertices, uvs, normals);

    // Indexed VBO
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexedVertices;
    std::vector<glm::vec2> indexedUVs;
    std::vector<glm::vec3> indexedNormals;
    indexVBO(vertices, uvs, normals, indices, indexedVertices, indexedUVs, indexedNormals);

    // Buffer for vertices.
    GLuint vertexBuffer;
    // 1 buffer and put result in vertexBuffer, then bind it.
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Hand our vertex data to OpenGL.
    //glBufferData(GL_ARRAY_BUFFER, indexedVertices.size() * sizeof(glm::vec3), &indexedVertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // Buffer for UVs.
    GLuint uvBuffer;
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    //glBufferData(GL_ARRAY_BUFFER, indexedUVs.size() * sizeof(glm::vec2), &indexedUVs[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    // Buffer for normals.
    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    //glBufferData(GL_ARRAY_BUFFER, indexedNormals.size() * sizeof(glm::vec3), &indexedNormals[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    // Buffer for indices (VBO).
    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    glUseProgram(programID);
    GLuint lightID = glGetUniformLocation(programID, "lightPosition_worldspace");

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    // do while loop keeps the window open until the ESCAPE key is pressed.
    do {

        // Measure speed.
        // 60 FPS = 16.6666 MS; 30 FPS = 33.3333 MS.
        double currentTime = glfwGetTime();
        nbFrames++;
        // 5 second intervals.
        if (currentTime - lastTime >= 5.0) {
            printf("%f ms / frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 5.0;
        }

        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader.
        glUseProgram(programID);

        // Compute the MVP matrix from keyboard and mouse.
        computeMatricesFromInputs();
        glm::mat4 projectionMatrix = getProjectionMatrix();
        glm::mat4 viewMatrix = getViewMatrix();
        glm::mat4 modelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Sends the MVP uniform.
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

        glm::vec3 lightPos = glm::vec3(2, 2, 2);
        glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureID, 0);

        // Vertex buffer.
        // Vertex shader will look at `layout(location = 0)`.
        glEnableVertexAttribArray(0);
        // Bind.
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        /*
        0: matches value in `glEnableVertexAttribArray();`
        3: size; glm::vec3
        GL_FLOAT: type
        GL_FALSE: normalized
        0: stride
        (void*)0: array buffer offset
        */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        // UV buffer.
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Normal buffer.
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Draw.
        // 0: starting vertex, total of vertices.
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        // Index buffer.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        // Draw indices.
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

        // Cleanup: disable to free memory.
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        // Swapping buffers and stuff.
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    
    // Cleanup. Always good to free up resources.
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &normalBuffer);
    glDeleteBuffers(1, &elementBuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Cleans up everything so the allocated resources are released and terminates GLFW.
    glfwTerminate();

    // Everything went smoothly.
    return 0;
}