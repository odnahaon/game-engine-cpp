// Standard includes.
#include <vector>
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
	int status = 1;

	// Open the file.
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Error: could not open file at %s.\n", path);
		return false;
	}

	while (1) {
		// Assumes the first word of a line isn't longer than 256, not ideal but it works for our purposes.
		char lineHeader[256];
		// Read the first word of the line.
		int res = fscanf(file, "%s", lineHeader);
		// Break the loop if line is the End Of File.
		if (res == EOF) {
			break;
		}
		// Read the vertices
		else if (strcmp(lineHeader, "v\0") == 0) {
			glm::vec3 vertex;
			status = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			if (status == 0) {
				printf("Could not find vertices in file %s\n", path);
				return false;
			}
			tempVertices.push_back(vertex);
		}
		// Read the UVs
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			status = fscanf(file, "%f %f \n", &uv.x, &uv.y);
			if (status == 0) {
				printf("Could not find UV in file %s\n", path);
				return false;
			}
			tempUvs.push_back(uv);
		}
		// Read the normals
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			status = fscanf(file, "%f %f %f \n", &normal.x, &normal.y, &normal.z);
			if (status == 0) {
				printf("Could not find normals in file %s\n", path);
				return false;
			}
			tempNormals.push_back(normal);
		}
		// Read the polygonal face elements
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File %s can't be read by our simple parser. Try exporting with other options, such as triangles.\n", path);
				return false;
			}
			if (matches == 0) {
				printf("Could not find polygonal face elements in file %s\n", path);
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
		// Comment in the file probably.
		else {
			// Assumes it is no longer than 1024 chars.
			char buffer[1024];
			fgets(buffer, 1000, file);
		}
	}

	// For each vertex of each triangle.
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = tempVertices[vertexIndex - 1];
		glm::vec2 uv = tempUvs[uvIndex - 1];
		glm::vec3 normal = tempNormals[normalIndex - 1];

		outVertices.push_back(vertex);
		outUvs.push_back(uv);
		outNormals.push_back(normal);
	}

	fclose(file);

	return true;
}