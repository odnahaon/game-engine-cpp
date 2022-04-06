#include <vector>
#include <glm/glm.hpp>
using namespace glm;

#include "tangentspace.hpp"

void computeTangentBasis(std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &tangents, std::vector<glm::vec3> &bitangents) {
	for (unsigned int i = 0; i < vertices.size(); i += 3) {
		glm::vec3& v0 = vertices[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(i) + 0];
		glm::vec3& v1 = vertices[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(i) + 1];
		glm::vec3& v2 = vertices[static_cast<std::vector<glm::vec3, std::allocator<glm::vec3>>::size_type>(i) + 2];

		glm::vec2& uv0 = uvs[static_cast<std::vector<glm::vec2, std::allocator<glm::vec2>>::size_type>(i) + 0];
		glm::vec2& uv1 = uvs[static_cast<std::vector<glm::vec2, std::allocator<glm::vec2>>::size_type>(i) + 1];
		glm::vec2& uv2 = uvs[static_cast<std::vector<glm::vec2, std::allocator<glm::vec2>>::size_type>(i) + 2];

		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
	}

	for (unsigned int i = 0; i < vertices.size(); i += 1) {
		glm::vec3 &n = normals[i];
		glm::vec3 &t = tangents[i];
		glm::vec3 &b = bitangents[i];
		t = glm::normalize(t - n * glm::dot(n, t));
		if (glm::dot(glm::cross(n, t), b) < 0.0f) {
			t = t * -1.0f;
		}
	}
}