#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "loadObj2.hpp"

//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#define TINYOBJLOADER_IMPLEMENTATION
#include "other/tiny_obj_loader.h"

bool loadObj2(const char* path, std::vector <glm::vec3>& outVertices, std::vector <glm::vec2>& outUvs, std::vector <glm::vec3>& outNormals) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

    if (!success) {
        printf("Error loading OBJ file: %s\n", err);
        return false;
    }


}