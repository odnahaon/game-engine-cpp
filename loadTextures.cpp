// Standard includes
#include <vector>
#include <string>
#include <iostream>

// GLEW.
#define GLEW_STATIC
#include <GL/glew.h>

// STB image loader.
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

unsigned int loadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    int errorCount = 0;
    int errorMax = 1024;
    bool e = false;
    for (unsigned int i = 0; i < faces.size(); i++) {
        int check = stbi_info(faces[i].c_str(), &width, &height, &nrChannels);
        if (check == 0 && errorCount <= errorMax) {
            std::cout << "Image info failed to load at path: \n" << faces[i] << ".\n" << std::endl;
            errorCount++;
        }
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            if (errorCount <= errorMax) {
                std::cout << "Cubemap tex failed to load at path: \n" << faces[i] << std::endl;
                errorCount++;
            }
            stbi_image_free(data);
        }
        if (errorCount >= errorMax && e != true) {
            e = true;
            std::cout << "Error max reached. Max: \n" << errorMax << std::endl;
        }
    }

    return textureID;
}