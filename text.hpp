#ifndef TEXT_RENDERER
#define TEXT_RENDERER

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

std::map<char, Character> Characters;

bool loadFont(const char* font);

#endif