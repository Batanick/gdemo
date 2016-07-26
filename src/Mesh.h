//
// Created by Evgenii Loikov
//

#ifndef GDEMO_MESH_H
#define GDEMO_MESH_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Mesh {
public:
    Mesh(const unsigned int vertexBuffer, const unsigned int indexBuffer, const unsigned int elementsSize) :
            vertexBuffer(vertexBuffer),
            indexBuffer(indexBuffer),
            elementsSize(elementsSize) { }

    unsigned int getVertexBuffer() const {
        return vertexBuffer;
    }

    unsigned int getIndexBuffer() const {
        return indexBuffer;
    }

    unsigned int getElementsSize() const {
        return elementsSize;
    }

    glm::mat4 getTransform() const {
        return glm::translate(glm::toMat4(rotation), position);
    }

private :
    const unsigned int vertexBuffer;
    const unsigned int indexBuffer;

    const unsigned int elementsSize;

    glm::vec3 position;
    glm::quat rotation;
};


#endif //GDEMO_MESH_H
