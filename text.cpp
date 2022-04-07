/*// Standard includes.
#include <map>
#include <utility>

// GLEW.
#define GLEW_STATIC
#include <GL/glew.h>

// GLM.
#include <glm/glm.hpp>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

#include "text.hpp"

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

std::map<char, Character> Characters;

bool loadFont(const char* font) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        printf("Error: Could not initialize FreeType library.\n");
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, font, 0, &face)) {
        printf("Error: Failed to load font at: %s\n", font);
        return false;
    }

    // Width and height. 0 lets it dynamically calculate width.
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            printf("Failed to load glyph at: %c\n", c);
            continue;
        }

        // Generate the texture.
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<unsigned int> (face->glyph->advance.x)};
        Characters.insert(std::pair<char, Character>(c, character));
    }
    // Cleanup.
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return true;
}
*/