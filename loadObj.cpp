// Standard includes.
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "loadObj.hpp"

bool loadObj (const char* path, std::vector < glm::vec3 >& out_vertices, std::vector < glm::vec2 >& out_uvs, std::vector < glm::vec3 >& out_normals) {
	// Variables to store info.
	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector <glm::vec3> temp_vertices;
	std::vector <glm::vec2> temp_uvs;
	std::vector <glm::vec3> temp_normals;

	return true;
}