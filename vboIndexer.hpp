#ifndef VBOINDEXER_HPP
#define VBOINDEXER_HPP

void indexVBO(std::vector<glm::vec3> &inVertices, std::vector<glm::vec2> &inUVs, std::vector<glm::vec3> &inNormals, std::vector<unsigned short> &outIndices, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals);

void indexVBO_TBN(std::vector<glm::vec3> &inVertices, std::vector<glm::vec2> &inUVs, std::vector<glm::vec3> &inNormals, std::vector<glm::vec3> &inTangents, std::vector<glm::vec3> &inBitangents, std::vector<unsigned short>& outIndices, std::vector<glm::vec3> &outVertices, std::vector<glm::vec2> &outUVs, std::vector<glm::vec3> &outNormals, std::vector<glm::vec3> &outTangents, std::vector<glm::vec3> &outBitangents);

#endif