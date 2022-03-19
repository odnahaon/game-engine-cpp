#ifndef OBJ_HPP
#define OBJ_HPP

/*struct mtl {
    std::string name;
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    double Ns;
    double Ni;
    char map_Ka;
    char map_Kd;
    char map_Ks;
    char map_Ns;
};*/

bool loadObj(const char* path, std::vector <glm::vec3> &outVertices, std::vector <glm::vec2> &outUvs, std::vector <glm::vec3> &outNormals);

//bool loadMtl(const char* path, std::vector <std::string> &name, std::vector <glm::vec3> &Ka, std::vector <glm::vec3> &Kd, std::vector <glm::vec3> &Ks, std::vector <double> &Ns, std::vector <double> &Ni);

#endif