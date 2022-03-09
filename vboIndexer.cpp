// Standard includes.
#include <vector>
#include <map>

// GLM.
#include <glm/glm.hpp>

#include "vboIndexer.hpp"

#include <string.h>

bool isNear(float v1, float v2) {
    return fabs(v1 - v2) < 0.01f;
}

bool getSimilarVertexIndex(glm::vec3& inVertex, glm::vec2& inUV, glm::vec3& inNormal, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUVs, std::vector<glm::vec3>& outNormals, unsigned short& result) {
    for (unsigned int i = 0; i < outVertices.size(); i++) {
        if (isNear(inVertex.x, outVertices[i].x) && isNear(inVertex.y, outVertices[i].y) && isNear(inVertex.z, outVertices[i].z) && isNear(inUV.x, outUVs[i].x) && isNear(inUV.y, outUVs[i].y) && isNear(inNormal.x, outNormals[i].x) && isNear(inNormal.y, outNormals[i].y) && isNear(inNormal.z, outNormals[i].z)) {
            result = i;
            return true;
        }
    }
    return false;
}

void indexVBOSlow(std::vector<glm::vec3>& inVertices, std::vector<glm::vec2>& inUVs, std::vector<glm::vec3>& inNormals, std::vector<unsigned short>& outIndices, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUVs, std::vector<glm::vec3>& outNormals) {
    for (unsigned int i = 0; i < inVertices.size(); i++) {
        unsigned short index;
        bool found = getSimilarVertexIndex(inVertices[i], inUVs[i], inNormals[i], outVertices, outUVs, outNormals, index);
        if (found) {
            outIndices.push_back(index);
        } else {
            outVertices.push_back(inVertices[i]);
            outUVs.push_back(inUVs[i]);
            outNormals.push_back(inNormals[i]);
            outIndices.push_back((unsigned short) outVertices.size() - 1);
        }
    }
}

struct packedVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    bool operator<(const packedVertex that) const {
        return memcmp((void*)this, (void*)&that, sizeof(packedVertex)) > 0;
    };
};

bool getSimilarVertexIndexFast(packedVertex &packed, std::map<packedVertex, unsigned short> &vertexToOutIndex, unsigned short &result) {
    std::map<packedVertex, unsigned short>::iterator it = vertexToOutIndex.find(packed);
    if (it == vertexToOutIndex.end()) {
        return false;
    } else {
        result = it -> second;
        return true;
    }
}

void indexVBO(std::vector<glm::vec3>& inVertices, std::vector<glm::vec2>& inUVs, std::vector<glm::vec3>& inNormals, std::vector<unsigned short>& outIndices, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUVs, std::vector<glm::vec3>& outNormals) {
    std::map<packedVertex, unsigned short> vertexToOutIndex;
    for (unsigned int i = 0; i < inVertices.size(); i++) {
        packedVertex packed = {inVertices[i], inUVs[i], inNormals[i]};

        unsigned short index;
        bool found = getSimilarVertexIndexFast(packed, vertexToOutIndex, index);
        if (found) {
            outIndices.push_back(index);
        } else {
            outVertices.push_back(inVertices[i]);
            outUVs.push_back(inUVs[i]);
            outNormals.push_back(inNormals[i]);
            unsigned short newIndex = (unsigned short) outVertices.size() - 1;
            outIndices.push_back(newIndex);
            vertexToOutIndex[packed] = newIndex;
        }
    }
}

void indexVBO_TBN(std::vector<glm::vec3>& inVertices, std::vector<glm::vec2>& inUVs, std::vector<glm::vec3>& inNormals, std::vector<glm::vec3>& inTangents, std::vector<glm::vec3>& inBitangents, std::vector<unsigned short>& outIndices, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUVs, std::vector<glm::vec3>& outNormals, std::vector<glm::vec3>& outTangents, std::vector<glm::vec3>& outBitangents) {
    for (unsigned int i = 0; i < inVertices.size(); i++) {
        unsigned short index;
        bool found = getSimilarVertexIndex(inVertices[i], inUVs[i], inNormals[i], outVertices, outUVs, outNormals, index);
        if (found) {
            outIndices.push_back(index);
            outTangents[index] += inTangents[i];
            outBitangents[index] += inBitangents[i];
        } else {
            outVertices.push_back(inVertices[i]);
            outUVs.push_back(inUVs[i]);
            outNormals.push_back(inNormals[i]);
            outTangents.push_back(inTangents[i]);
            outBitangents.push_back(inBitangents[i]);
            outIndices.push_back((unsigned short) outVertices.size() - 1);
        }
    }
}