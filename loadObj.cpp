// Standard includes.
/*#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "loadObj.hpp"

bool loadObj (const char* path, std::vector <glm::vec3> &outVertices, std::vector <glm::vec2> &outUvs, std::vector <glm::vec3> &outNormals) {
	// Variables to store info.
	std::vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector <glm::vec3> tempVertices;
	std::vector <glm::vec2> tempUvs;
	std::vector <glm::vec3> tempNormals;

	// Open file and catch errors.
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Error opening file.\n");
		return false;
	}
	
	// Read the file.
	while (1) {
		char lineHeader[128];
		int res = fscanf_s(file, "%s", lineHeader);
		// End of file check.
		if (res == EOF) {
			break;
		}

		if (strcmp(lineHeader, "v") == 0) {
			// Read the vertices.
			glm::vec3 vertex;
			fscanf_s(file, "$f $f $f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		} else if (strcmp(lineHeader, "vt") == 0) {
			// Read the texture coordiates of the vertices.
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			tempUvs.push_back(uv);
		} else if (strcmp(lineHeader, "vn") == 0) {
			// Read the normals.
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			// Read the faces.
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read. Please export with the .OBJ file format.\nOnly check the \"Apply Modifiers\", \"Include Normals\", \"Include UVs\", and \"Triangulate Faces\" options.");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	// Vertices of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = tempVertices[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(vertexIndex) - 1];
		glm::vec2 uv = tempUvs[static_cast<std::vector<glm::vec2, std::allocator<glm::vec2>>::size_type>(uvIndex) - 1];
		glm::vec3 normal = tempNormals[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(normalIndex) - 1];

		outVertices.push_back(vertex);
		outUvs.push_back(uv);
		outNormals.push_back(normal);
	}
	fclose(file);
	return true;
}*/