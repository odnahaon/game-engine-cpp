// GLEW.
#define GLEW_STATIC
#include <GL/glew.h>

// STB image loader.
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void loadTextures(char* filename, int width, int height, int colorChannels) {

	// Create ID and generate textures and mipmaps.
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	/* 
	* Texture properties:
	* Repeats on the x-axis.
	* Repeats on the y-axis.
	* Repeats on the z-axis.
	* Closer? Blur the texture.
	* Farther? Sharpen the texture.
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load an image from parameters.
	unsigned char* data = stbi_load(filename, &width, &height, &colorChannels, 0);

	// Check for the data and throw error messages.
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Failed to load texture.\n");
	}

	// Free memory.
	stbi_image_free(data);
}