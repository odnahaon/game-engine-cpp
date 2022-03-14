#ifndef OBJ_HPP
#define OBJ_HPP

struct mtl {
    char name;
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    double Ns;
    double Ni;
    char map_Ka;
    char map_Kd;
    char map_Ks;
    char map_Ns;
};

bool loadObj(const char* path, std::vector <glm::vec3> &outVertices, std::vector <glm::vec2> &outUvs, std::vector <glm::vec3> &outNormals, std::vector <char> &outMaterialFile);

bool loadMtl(const char* path, std::vector <mtl> &materials);

#endif